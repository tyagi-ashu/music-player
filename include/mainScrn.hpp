#pragma once
#include "playScrn.hpp"
#include "songsScrn.hpp"
#include "mainScrn.hpp"
#include "screen.hpp"
#include "button.hpp"
class mainScrn:public screen{
    private:
    Texture2D texture;
    //needed the pointer because font wasnt loading properly
    Button *playButton;
    Button *songsButton;
    Font font;
    int font_height=24;
    public:
    mainScrn(){
        texture=LoadTexture("../resources/title.png");
        font=LoadFontEx("../resources/my-font.ttf",font_height,NULL,0);
        //its not in render() so that it dosent render again and again and again
        playButton = new Button("PLAYLIST",{400,100},font_height,font);
        songsButton = new Button("SONGS LIST",{400,250},font_height,font);
    }
    ~mainScrn(){
        delete playButton;
        delete songsButton;
        UnloadTexture(texture);
    }
    //static function passed for error "void (mainScrn::*)()" is incompatible with parameter of type "void (*)()"
    static void playButtonFunc(){
        s=screens::playscrn;
    }
    static void songsButtonFunc(){
        s=screens::songsscrn;
    }
    void display(){
        DrawTextureV(texture,{0,0},RAYWHITE);
        playButton->Draw(playButtonFunc);
        songsButton->Draw(songsButtonFunc);
    }
};