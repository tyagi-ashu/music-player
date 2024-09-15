#pragma once
#include "playScrn.hpp"
#include "mainScrn.hpp"
#include "screen.hpp"
#include "button.hpp"
#include "playlist.hpp"

class playScrn:public screen{
    private:
    
    //needed the pointer because font wasnt loading properly
    Button *mainButton;
    int song_index=0;
    int capacity=3;
    public:
    playScrn(){
        //its not in render() so that it dosent render again and again and again
        mainButton = new Button("back",{50,screenHeight-50},font_height,font);
    }
    ~playScrn(){
        delete mainButton;
    }
    //static-- to access this function when there is no instance of this class and 'draw' is called 
    static void mainButtonFunc(){
        s=screens::mainscrn;
    }
    void display(){
        int temp_song_index=0;
        UpdateMusicStream(music);
        DrawTextureV(texture,{0,0},RAYWHITE);
        mainButton->Draw(mainButtonFunc);
        float posX;
        float font_width;
        float posY=300;
        const char* name;
        DrawTextEx(font,"playlist",{screenWidth/2 - 65,posY},font_height,0,BLACK);
        posY=posY+5;
        DrawText("____________________________________",screenWidth/2-240,posY,font_height,BLACK);
        if(!p.count){
            posY=font_height+posY+5;
            DrawTextEx(font,"empty",{screenWidth/2 - 15,posY},font_height,0,BLACK);
        }
        else{
            if(song_index<p.count && song_index+capacity<p.count){
                DrawTextEx(font,"D-next",{screenWidth-100, screenHeight-50},font_height,0,BLACK);
            }
            if(song_index){
                DrawTextEx(font,"A-prev",{screenWidth-200, screenHeight-50},font_height,0,BLACK);
            }
            DrawTextEx(font,"S-shuffle",{screenWidth-400, screenHeight-50},font_height,0,BLACK);
            if(IsKeyPressed(KEY_S)){
                p.make_shuffle();
                song_index=0;
                temp_song_index=0;
            }
            for(int i =song_index;i<p.count && i<song_index+capacity;i++){
                name=TextToLower((p.vec[i].second).c_str());
                posX=screenWidth/2 - MeasureTextEx(font,name,font_height,0).x/2;
                posY=font_height+posY+5;
                font_width=MeasureTextEx(font,name,font_height,0).x;
                Vector2 mousePos=GetMousePosition();
                if(mousePos.x>posX && mousePos.x<posX+font_width && mousePos.y>posY && mousePos.y<posY+font_height){
                    DrawTextEx(font,name,{posX,posY},font_height,0,RED);
                    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                        p.remove_song_name(name);
                        song_index=0;
                        temp_song_index=0;
                        break;
                    }
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        string path="../resources/music/"+p.vec[i].first+"/"+p.vec[i].second+".mp3";
                        music = LoadMusicStream(path.c_str());
                        PlayMusicStream(music);
                    }
                }
                else{
                    DrawTextEx(font,name,{posX,posY},font_height,0,BLACK);
                } 
                temp_song_index++;
            }
            if(song_index<p.count && song_index+capacity<p.count && IsKeyPressed(KEY_D)){
                song_index+=capacity;
            }

            if (song_index && IsKeyPressed(KEY_A)){
                song_index-=capacity;
            }
        }
    }
};