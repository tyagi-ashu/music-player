#include "raylib.h"
#include "playlist.hpp"
#include "screen.hpp"
#include "button.hpp"
#include "logoScrn.hpp"
#include "mainScrn.hpp"
#include "playScrn.hpp"
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
    screen *s=new logoScrn;
    while (!WindowShouldClose())
    {
        s->display();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();

    return 0;
}