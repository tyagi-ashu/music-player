#pragma once
#include "songsScrn.hpp"
#include "mainScrn.hpp"
#include "screen.hpp"
#include "button.hpp"

class songsScrn: public screen{
    private:

    Button *mainButton;
    int song_index=0;
    int capacity=7;
    vector<pair<string,string>> vec;
    int vec_size;
    bool musicPlaying=false;
    bool play_interrupted=false;
    public:
    songsScrn(){
        vec=musicFile::read_music_files();
        vec_size=vec.size();

        mainButton = new Button("back",{rectPos+20,screenHeight-10},font_height,font);
    }
    ~songsScrn(){
        delete mainButton;
    }

    static void mainButtonFunc(){

        s=screens::mainscrn;
    }
    void display(){
        UpdateMusicStream(music);
        int temp_song_index=0;
        if(!play_interrupted){
            mainButton->Draw(mainButtonFunc);
        }
        float posX;
        float posY=rectPos+100;
        const char* name;
        float font_width;
        DrawTextEx(font,"song list",{screenWidth/2 - 44,posY},font_height,0,BLACK);
        posY=posY+20;
        DrawText("____________________________________",screenWidth/2-300,posY,font_height,BLACK);
        if(!vec_size){
            posY=font_height+posY+5;
            DrawTextEx(font,"empty",{screenWidth/2 - 15,posY},font_height,0,BLACK);
        }
        else{
            DrawTextEx(font,"l-click add",{screenWidth-150,rectPos+10},18,0,BLACK);
            DrawTextEx(font,"r-click demo play",{screenWidth-150,rectPos+27},18,0,BLACK);
            if(song_index<vec_size && song_index+capacity<vec_size){
                DrawTextEx(font,"D-next",{screenWidth-100, screenHeight-10},font_height,0,BLACK);
            }
            if(song_index){
                DrawTextEx(font,"A-prev",{screenWidth-250, screenHeight-10},font_height,0,BLACK);
            }
            for(int i =song_index;i<vec_size && i<song_index+capacity;i++){
                name=TextToLower((vec[i].second.c_str()));
                posX=screenWidth/2 - MeasureTextEx(font,name,font_height,0).x/2 + rectPos;
                posY=font_height+posY+5;
                font_width=MeasureTextEx(font,name,font_height,0).x;
                Vector2 mousePos=GetMousePosition();
                if(mousePos.x>posX && mousePos.x<posX+font_width && mousePos.y>posY && mousePos.y<posY+font_height){
                    DrawTextEx(font,name,{posX,posY},font_height,0,RED);
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        //insert at end
                        p.add_song(vec[i]);
                        break;
                    }
                    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                        if(IsMusicStreamPlaying(music)){
                            play_interrupted=true;
                            music2=music;
                            PauseMusicStream(music);
                        }
                        string path="../resources/music/"+vec[i].first+"/"+vec[i].second+".mp3";
                        music = LoadMusicStream(path.c_str());
                        PlayMusicStream(music);
                        musicPlaying=true;
                    }
                }
                else{
                    DrawTextEx(font,name,{posX,posY},font_height,0,BLACK);
                } 
                temp_song_index++;
            }
            //plays 10% of music for trial purposes
            if(musicPlaying){
                DrawTextEx(font,"E-end",{screenWidth-450, screenHeight-10},font_height,0,BLACK);
                float timePlayed = GetMusicTimePlayed(music)/GetMusicTimeLength(music);
                if (timePlayed > 0.10f) timePlayed = 0.10f;
                if(timePlayed==0.10f || IsKeyPressed(KEY_E)){
                    StopMusicStream(music);
                    musicPlaying=false;
                    if(play_interrupted){
                        music=music2;
                        ResumeMusicStream(music);
                        play_interrupted=false;
                    }
                }
            }
            if(song_index<vec_size && song_index+capacity<vec_size && IsKeyPressed(KEY_D)){
                song_index+=capacity;
            }

            if (song_index && IsKeyPressed(KEY_A)){
                song_index-=capacity;
            }
        }
    }
};