#pragma once
#include "songsScrn.hpp"
#include "mainScrn.hpp"
#include "screen.hpp"
#include "button.hpp"
#include "searchSong.hpp"
#include <algorithm>
class songsScrn: public screen{
    private:
    trie t;

    Button *mainButton;
    int song_index=0;
    int capacity=7;

    vector<pair<string,string>> vec;
    int vec_size;

    bool musicPlaying=false;
    bool play_interrupted=false;

    int key_entered;
    string word;
    bool word_hovered=false;
    public:
    songsScrn(){

        vec=musicFile::read_music_files();
        vec_size=vec.size();
        if(vec_size){
            for(auto i:vec){
                string word=i.second;
                transform(word.begin(),word.end(),word.begin(), ::tolower);
                t.insertSong(word,i.first);
            }
        }
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
        //created so that i accedently dont change the original vec
        vector<pair<string,string>> temp_vec={};
        int temp_vec_size=0;
        int temp_song_index=0;

        if(!play_interrupted){
            mainButton->Draw(mainButtonFunc);
        }
        Vector2 mousePos=GetMousePosition();
        float posX;
        float posY=200;
        const char* name;
        float font_width;
        float wordPosX;
        if(word.length()==0){
            DrawTextEx(font,"song list",{screenWidth/2 - 44,posY},font_height,0,BLACK);
        }
        else{
            DrawTextEx(font,"song",{screenWidth/2,posY},font_height,0,BLACK);
        }
        posY=posY+20;
        DrawText("____________________________________",screenWidth/2-300,posY,font_height,BLACK);
        if(!vec_size){
            posY=font_height+posY+5;
            DrawTextEx(font,"empty",{screenWidth/2 - 15,posY},font_height,0,BLACK);
        }
        else{
            DrawTextEx(font,"l-click add",{screenWidth-150,rectPos+10},18,0,BLACK);
            DrawTextEx(font,"r-click demo play",{screenWidth-150,rectPos+27},18,0,BLACK);
            DrawTextEx(font,"hover to type",{screenWidth-150,rectPos+44},18,0,BLACK);
            DrawTextEx(font,"search:",{rectPos+100,rectPos+100},font_height,0,BLACK);
            posX=rectPos+250;
            font_width=500;//size of rectangle box;
            wordPosX=posX +4;
            if(mousePos.x>posX && mousePos.x<posX+font_width && mousePos.y>rectPos+100 && mousePos.y<rectPos+100+font_height){
                word_hovered=true;
                DrawRectangleLines(posX,rectPos+100,500,font_height,LIGHTGRAY);
                key_entered=GetCharPressed();
                //24 char allowed
                if((key_entered >= 32) && (key_entered <= 125) && word.length()<=24){
                    wordPosX+=font_height+2;
                    word+=char(tolower(char(key_entered)));
                }
                if (word.length() && (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE))){
                    wordPosX-=font_height-2;
                    word=word.substr(0,word.length()-1);
                }
            }
            else{
                word_hovered=false;
                DrawRectangleLines(posX,rectPos+100,500,font_height,BLACK);
            }
            if(word.length()!=0){
                pair<bool,string> result=t.searchSong(word);
                if(result.first){
                    temp_vec.push_back(make_pair(result.second,word));
                    temp_vec_size=1;
                }
                else{
                    temp_vec_size=0;
                }
            }
            else{
                temp_vec=vec;
                temp_vec_size=vec_size;
            }

            DrawText(word.c_str(),wordPosX,rectPos+100,font_height,BLACK);

            if(song_index<temp_vec_size && song_index+capacity<temp_vec_size){
                DrawTextEx(font,"D-next",{screenWidth-100, screenHeight-10},font_height,0,BLACK);
            }
            if(song_index){
                DrawTextEx(font,"A-prev",{screenWidth-250, screenHeight-10},font_height,0,BLACK);
            }
            for(int i =song_index;i<temp_vec_size && i<song_index+capacity;i++){
                name=TextToLower((temp_vec[i].second.c_str()));
                posX=screenWidth/2 - MeasureTextEx(font,name,font_height,0).x/2 + rectPos;
                posY=font_height+posY+5;
                font_width=MeasureTextEx(font,name,font_height,0).x;
                if(mousePos.x>posX && mousePos.x<posX+font_width && mousePos.y>posY && mousePos.y<posY+font_height){
                    DrawTextEx(font,name,{posX,posY},font_height,0,RED);
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        //insert at end
                        p.add_song(temp_vec[i]);
                        break;
                    }
                    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                        if(IsMusicStreamPlaying(music)){
                            play_interrupted=true;
                            music2=music;
                            PauseMusicStream(music);
                        }
                        string path="../resources/music/"+temp_vec[i].first+"/"+temp_vec[i].second+".mp3";
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
            if(!word_hovered && song_index<temp_vec_size && song_index+capacity<temp_vec_size && IsKeyPressed(KEY_D)){
                song_index+=capacity;
            }

            if (!word_hovered && song_index && IsKeyPressed(KEY_A)){
                song_index-=capacity;
            }
        }
    }
};