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
        Rectangle rect={position.x,position.y,static_cast<float>(w),static_cast<float>(h)};
        if(CheckCollisionPointRec(mousePos,rect)){
            return true;
        }
        return false;
        //return (mousePos.x>x && mousePos.x<x+font_width && mousePos.y>y && mousePos.y<y+font_height);
    }
    
    public:
    Button(std::string n,Vector2 pos,float fh){
        //font height=fh
        name=n;
        position=pos;
        font = LoadFontEx("../resources/my-font.ttf",fh,NULL,0);
        w=MeasureTextEx(font,name.c_str(),fh,0).x;
        h=fh;
        Wave selectSound=LoadWave("../resources/button-pressed.wav");
        selectAsSound=LoadSoundFromWave(selectSound);
        UnloadWave(selectSound);
    }
    ~Button(){
        UnloadFont(font);
    }
    void Draw(void (*on_click)()){
        //checking hovering
        DrawRectangle(position.x,position.y,w,h,(isHovered(GetMousePosition()) ? BLACK : RAYWHITE));
        DrawTextEx(font,name.c_str(),position,h,0,(isHovered(GetMousePosition()) ? RED : YELLOW));
        if(isHovered(GetMousePosition())){
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                PlaySound(selectAsSound);
                on_click();
            }
        }
    }
};