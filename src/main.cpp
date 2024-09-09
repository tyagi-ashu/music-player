#include "raylib.h"
#include <iostream>
#include "button.hpp"
#include "playlist.hpp"
int main(void){

    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Music Player");
    InitAudioDevice();
    SetTargetFPS(60);
    Button playerButton("playerkjbjhbjhagsd",{350,150},32);
    //to add all the music files and making playlist
    musicFile mf;
    mf.add_music_file();
    //playlist automatically read files...so dont call read_file function
    playlist p;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        playerButton.Draw();
        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
