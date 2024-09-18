#pragma once
#include "raylib.h"
#include <iostream>
#include <string>
//x,y,width,height for rectangles
class Button{
    private:
    Sound selectAsSound;
    Vector2 position;
    float w,h;   //width,height of text
    std::string name;
    Font font;

    bool isHovered(Vector2 mousePos){

        return (mousePos.x>position.x && mousePos.x<position.x+w && mousePos.y>position.y && mousePos.y<position.y+h);
    }
    public:
    Button(std::string n,Vector2 pos,float fh,Font f){
        //font height=fh
        this->name=n;
        this->position=pos;
        this->font = f;
        this->w=MeasureTextEx(font,name.c_str(),fh,0).x;
        this->h=fh;
        Wave selectSound=LoadWave("../resources/button-pressed.wav");
        selectAsSound=LoadSoundFromWave(selectSound);
        SetSoundVolume(selectAsSound,0.3);
        UnloadWave(selectSound);
    }
    ~Button(){
        UnloadFont(font);
    }
    void Draw(void (*on_click)()){
        DrawRectangle(position.x,position.y,w,h,RAYWHITE);
        if(isHovered(GetMousePosition())){
            DrawTextEx(font,TextToUpper(name.c_str()),position,h,0,BLACK);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                PlaySound(selectAsSound);
                on_click();
            }
        }
        else{
            DrawTextEx(font,name.c_str(),position,h,0,BLACK);
        }
    }
};