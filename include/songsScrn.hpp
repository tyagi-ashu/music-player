#pragma once
#include "songsScrn.hpp"
#include "mainScrn.hpp"
#include "screen.hpp"
#include "button.hpp"
//remove button and add welcome fadeing text and a timer to go to main screen
class songsScrn: public screen{
    private:
    Texture2D texture;
    //needed the pointer because font wasnt loading properly
    Button *mainButton;
    Font font;
    int font_height=24;
    float screenHeight;
    float screenWidth;
    int song_index=0;
    int capacity=8;
    vector<pair<string,string>> vec;
    int vec_size;
    public:
    songsScrn(){
        vec=musicFile::read_music_files();
        vec_size=vec.size();
        screenHeight=GetScreenHeight();
        screenWidth=GetScreenWidth();
        texture=LoadTexture("../resources/title.png");
        font=LoadFontEx("../resources/my-font.ttf",font_height,NULL,0);
        //its not in render() so that it dosent render again and again and again
        mainButton = new Button("back",{50,screenHeight-50},font_height,font);
    }
    ~songsScrn(){
        delete mainButton;
        UnloadTexture(texture);
    }
    //static function passed for error "void (mainScrn::*)()" is incompatible with parameter of type "void (*)()"
    static void mainButtonFunc(){
        s=screens::mainscrn;
    }
    void display(){
        UpdateMusicStream(music);
        int temp_song_index=0;
        DrawTextureV(texture,{0,0},RAYWHITE);
        mainButton->Draw(mainButtonFunc);
        float posX;
        float posY=300;
        const char* name;
        float font_width;
        DrawTextEx(font,"song list",{screenWidth/2 - 65,posY},font_height,0,BLACK);
        posY=posY+5;
        DrawText("____________________________________",screenWidth/2-240,posY,font_height,BLACK);
        if(!vec_size){
            posY=font_height+posY+5;
            DrawTextEx(font,"empty",{screenWidth/2 - 15,posY},font_height,0,BLACK);
        }
        else{
            if(song_index<vec_size && song_index+capacity<vec_size){
                DrawTextEx(font,"D-next",{screenWidth-100, screenHeight-50},font_height,0,BLACK);
            }
            if(song_index){
                DrawTextEx(font,"A-prev",{screenWidth-200, screenHeight-50},font_height,0,BLACK);
            }
            for(int i =song_index;i<vec_size && i<song_index+capacity;i++){
                name=TextToLower((vec[i].second.c_str()));
                posX=screenWidth/2 - MeasureTextEx(font,name,font_height,0).x/2;
                posY=font_height+posY+5;
                font_width=MeasureTextEx(font,name,font_height,0).x;
                Vector2 mousePos=GetMousePosition();
                if(mousePos.x>posX && mousePos.x<posX+font_width && mousePos.y>posY && mousePos.y<posY+font_height){
                    DrawTextEx(font,name,{posX,posY},font_height,0,RED);
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        //insert at end
                        p.add_song(vec[i]);
                        song_index=0;
                        temp_song_index=0;
                        break;
                    }
                }
                else{
                    DrawTextEx(font,name,{posX,posY},font_height,0,BLACK);
                } 
                temp_song_index++;
            }
            if(song_index<vec_size && song_index+capacity<vec_size && IsKeyPressed(KEY_D)){
                song_index+=capacity;
            }

            if (song_index && IsKeyPressed(KEY_A)){
                song_index-=capacity;
            }
        }
    }
};