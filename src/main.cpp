#include "raylib.h"
#include "playlist.hpp"
#include "logoScrn.hpp"
#include "screen.hpp"

//add option scrn
//add exit scrn
int main(void){
    const int screenWidth = 900;
    const int screenHeight = 650;
    InitWindow(screenWidth, screenHeight, "Music Player");
    InitAudioDevice();
    SetTargetFPS(60);
    float rectPos=40;
    Rectangle rect={rectPos,rectPos,screenWidth-2*rectPos,screenHeight-2*rectPos};
    Texture2D texture=LoadTexture("../resources/title.png");
    //to add all the music files and making playlist
    musicFile::add_music_file();
    screen* nextState;
    screen* logoState=new logoScrn();
    screen* mainState=new mainScrn();
    screen* playState=new playScrn();
    screen* songsState=new songsScrn();
    screen* playerState=new playerScrn();
    screen* optionState= new optionScrn();
    s=screens::logoscrn;
    while (!WindowShouldClose())
    {
        switch(s){
            case screens::logoscrn:
            nextState=logoState;
            break;
            case screens:: mainscrn:
            nextState=mainState;
            break;
            case screens:: playscrn:
            nextState=playState;
            break;
            case screens::songsscrn:
            nextState= songsState;
            break;
            case screens:: playerscrn:
            nextState=playerState;
            break;
            case screens:: optionscrn:
            nextState=optionState;
            break;
            default:
            nextState=logoState;
            break;
        }


        BeginDrawing();
        ClearBackground(RAYWHITE);
        nextState->display();
        DrawRectangleLinesEx(rect,10,BLACK);
        
        DrawTextureV(texture,{rectPos-5,rectPos-5},RAYWHITE);
        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();

    return 0;
}