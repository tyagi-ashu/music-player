#include "raylib.h"
#include <iostream>
#include "mainScrn.hpp"
#include "playlist.hpp"
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
    p.print();
    p.make_shuffle();
    p.print();

    mainScrn m1;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        m1.render();
        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
