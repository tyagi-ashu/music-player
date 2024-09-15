#pragma once
#include "raylib.h"
class screen{
    public:
    //virtual-- so that while destructing diff screens using this class, no undefined behaviour dont occur
    //unload font and texture here
    virtual ~screen(){
    };    
    virtual void display(){};
    float font_height=24;
    float screenWidth=GetScreenWidth();
    float screenHeight=GetScreenHeight();
    Font font=LoadFontEx("../resources/my-font.ttf",font_height,NULL,0);
    Texture2D texture=LoadTexture("../resources/title.png");
};
enum class screens{
    logoscrn,
    mainscrn,
    playscrn,
    songsscrn,
    playerscrn
} s;

playlist p;
Music music;