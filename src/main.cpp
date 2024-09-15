#include "raylib.h"
#include "playlist.hpp"
#include "logoScrn.hpp"
#include "screen.hpp"
int main(void){
    const int screenWidth = 900;
    const int screenHeight = 650;
    InitWindow(screenWidth, screenHeight, "Music Player");
    InitAudioDevice();
    SetTargetFPS(60);
    
    //to add all the music files and making playlist
    musicFile::add_music_file();
    screen* nextState;
    screen* logoState=new logoScrn();
    screen* mainState=new mainScrn();
    screen* playState=new playScrn();
    screen* songsState=new songsScrn();
    screen* playerState=new playerScrn();
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
            default:
            nextState=logoState;
            break;
        }


        BeginDrawing();
        ClearBackground(RAYWHITE);
        nextState->display();
        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();

    return 0;
}