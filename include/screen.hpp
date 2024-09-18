#pragma once
#include "raylib.h"
class screen{
    public:
    //virtual-- so that while destructing diff screens using this class, no undefined behaviour dont occur
    //unload font and texture here
    virtual ~screen(){
    };    
    virtual void display(){};
    float font_height=32;
    float font2_height=60;
    Font font=LoadFontEx("../resources/my-font.ttf",font_height,NULL,0);
    Font font2=LoadFontEx("../resources/Arrows.ttf",font2_height,NULL,0);
    float rectPos=40;
    float screenWidth=GetScreenWidth()-2*rectPos;
    float screenHeight=GetScreenHeight()-2*rectPos;
};
enum class screens{
    logoscrn,
    mainscrn,
    playscrn,
    songsscrn,
    playerscrn,
} s;

playlist p;
Music music;
