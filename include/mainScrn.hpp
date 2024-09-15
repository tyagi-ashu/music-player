#pragma once
#include "playScrn.hpp"
#include "songsScrn.hpp"
#include "playerScrn.hpp"
#include "mainScrn.hpp"
#include "screen.hpp"
#include "button.hpp"
class mainScrn:public screen{
    private:
    //needed the pointer because font wasnt loading properly
    Button *playButton;
    Button *songsButton;
    Button *playerButton;
    public:
    mainScrn(){
        //its not in render() so that it dosent render again and again and again
        playButton = new Button("PLAYLIST",{400,100},font_height,font);
        playerButton = new Button("PLAYER",{400,170},font_height,font);
        songsButton = new Button("SONGS LIST",{400,250},font_height,font);
    }
    ~mainScrn(){
        delete playButton;
        delete songsButton;
        delete playerButton;
    }
    //static function passed for error "void (mainScrn::*)()" is incompatible with parameter of type "void (*)()"
    static void playButtonFunc(){
        s=screens::playscrn;
    }
    static void songsButtonFunc(){
        s=screens::songsscrn;
    }
    static void playerButtonFunc(){
        s=screens::playerscrn;
    }
    void display(){
        UpdateMusicStream(music);
        DrawTextureV(texture,{0,0},RAYWHITE);
        playButton->Draw(playButtonFunc);
        playerButton->Draw(playerButtonFunc);
        songsButton->Draw(songsButtonFunc);
    }
};