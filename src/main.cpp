#include "raylib.h"
#include "playlist.hpp"
#include "logoScrn.hpp"
#include "scrnManager.hpp"
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
    logoScrn *l = new logoScrn();
    ScrnManager::LoadScrn(l);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if(ScrnManager::ScrnLoaded()){
            ScrnManager::Update();
        }
        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();

    return 0;
}