#include "raylib.h"
#include "playlist.hpp"
#include "logoScrn.hpp"
#include "screen.hpp"
int main(void){
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Music Player");
    InitAudioDevice();
    SetTargetFPS(60);
    
    //to add all the music files and making playlist
    musicFile mf;
    mf.add_music_file();
    playlist p;
    screen* nextState;
    screen* logoState=new logoScrn();
    screen* mainState=new mainScrn();
    screen* playState=new playScrn();
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
            case screens:: null:
            std::cout<<"nothing selected"<<std::endl;
            nextState=logoState;
            break;
        }
        nextState->display();


        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();

    return 0;
}