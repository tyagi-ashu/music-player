#pragma once
#include "playerScrn.hpp"
#include "mainScrn.hpp"
#include "screen.hpp"
#include "button.hpp"
#include "playlist.hpp"

class playerScrn:public screen{
    private:
    Button *mainButton;
    bool playNext=false;
    public:
    playerScrn(){
        mainButton = new Button("back",{50,screenHeight-50},font_height,font);
    }
    ~playerScrn(){
        delete mainButton;
    }
    static void mainButtonFunc(){
        s=screens::mainscrn;
    }
    void display(){
        UpdateMusicStream(music);
        DrawTextureV(texture,{0,0},RAYWHITE);
        mainButton->Draw(mainButtonFunc);
        DrawTextEx(font,"P-play",{screenWidth-500, screenHeight-200},font_height,0,BLACK);
        if(IsKeyPressed(KEY_P)){
            playNext=true;
        }
        if(p.head!=NULL && playNext){
            string path=p.get_path();
            music = LoadMusicStream(path.c_str());
            PlayMusicStream(music);
        }
        if(GetMusicTimeLength(music)!=0){
            float timePlayed = GetMusicTimePlayed(music)/GetMusicTimeLength(music);
            if (timePlayed > 0.95f) timePlayed = 1.0f;
            if(timePlayed==1.0f){
                playNext=true;
                StopMusicStream(music);
            }
            else{
                playNext=false;
            }
        }
        else{
            playNext=false;
        }

    }
};