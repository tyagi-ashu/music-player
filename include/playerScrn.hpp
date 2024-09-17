#pragma once
#include "playerScrn.hpp"
#include "mainScrn.hpp"
#include "screen.hpp"
#include "button.hpp"
#include "playlist.hpp"
//play prev
//after shuffle same song goes on unless next is pressed 
class playerScrn:public screen{
    private:
    Button *mainButton;
    bool playNext=false;
    bool play=false;
    public:
    playerScrn(){
        mainButton = new Button("back",{rectPos+20,screenHeight-10},font_height,font);
    }
    ~playerScrn(){
        delete mainButton;
    }
    static void mainButtonFunc(){
        s=screens::mainscrn;
    }
    void display(){
        UpdateMusicStream(music);
        mainButton->Draw(mainButtonFunc);
        float posY=screenHeight/2+200;
        Vector2 mousePos=GetMousePosition();
        float posX=screenWidth/2;
        float font2_width=MeasureTextEx(font2,"Q",font2_height,0).x;
        if(mousePos.x>posX && mousePos.x<posX+font2_width && mousePos.y>posY && mousePos.y<posY+font2_height){
            DrawTextEx(font2,"Q",{posX, posY},font2_height,0,RED);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsMusicStreamPlaying(music)){
                play=false;
            }
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !IsMusicStreamPlaying(music)){
                play=true;
            }
        }
        else{
            DrawTextEx(font2,"Q",{posX,posY},font2_height,0,BLACK);
        }
        posX=screenWidth/2+80;
        font2_width=MeasureTextEx(font2,"I",font2_height,0).x;
        if(mousePos.x>posX && mousePos.x<posX+font2_width && mousePos.y>posY && mousePos.y<posY+font2_height){
            DrawTextEx(font2,"I",{posX, posY},font2_height,0,RED);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                playNext=true;
                play=true;
            }
        }
        else{
            DrawTextEx(font2,"I",{posX,posY},font2_height,0,BLACK);
        }

        if(p.head!=NULL && (playNext || !IsMusicReady(music)) && play){
            string path=p.get_path();
            music = LoadMusicStream(path.c_str());
            PlayMusicStream(music);
        }
        else if(p.head!=NULL && IsMusicReady(music) && play){
            ResumeMusicStream(music);
        }
        else if(p.head!=NULL && IsMusicReady(music) && !play){
            PauseMusicStream(music);
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
            play=false;
        }

    }
};