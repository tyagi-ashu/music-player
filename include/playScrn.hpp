#pragma once
#include "playScrn.hpp"
#include "mainScrn.hpp"
#include "screen.hpp"
#include "button.hpp"
#include "playlist.hpp"

class playScrn:public screen{
    private:
    Texture2D texture;
    //needed the pointer because font wasnt loading properly
    Button *mainButton;
    float font_height=24;
    float screenHeight;
    playlist p;
    Font font;
    int song_index=0;
    int capacity=3;
    public:
    playScrn(){
        screenHeight=GetScreenHeight();
        texture=LoadTexture("../resources/title.png");
        font=LoadFontEx("../resources/my-font.ttf",font_height,NULL,0);
        //its not in render() so that it dosent render again and again and again
        mainButton = new Button("back",{50,screenHeight-50},font_height,font);
    }
    ~playScrn(){
        delete mainButton;
        UnloadTexture(texture);
    }
    //static-- to access this function when there is no instance of this class and 'draw' is called 
    static void mainButtonFunc(){
        s=screens::mainscrn;
    }

    void display(){
        int temp_song_index=0;
        
        DrawTextureV(texture,{0,0},RAYWHITE);
        mainButton->Draw(mainButtonFunc);
        float posX;
        float posY=300;
        const char* name;
        float screenWidth=GetScreenWidth();
        DrawTextEx(font,"playlist",{screenWidth/2 - 65,posY},font_height,0,BLACK);
        posY=posY+5;
        DrawText("____________________________________",screenWidth/2-240,posY,font_height,BLACK);
        if(!p.count){
            posY=posY+5;
            DrawTextEx(font,"empty",{screenWidth/2 - 10,posY},font_height,0,BLACK);
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
            for(int i =song_index;i<p.count && i<song_index+3;i++){
                name=TextToLower((p.vec[i].first).c_str());
                posX=screenWidth/2 - MeasureTextEx(font,name,font_height,0).x/2;
                posY=font_height+posY+5;
                DrawTextEx(font,name,{posX,posY},font_height,0,BLACK);
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