#pragma once
#include "playScrn.hpp"
#include "songsScrn.hpp"
#include "playerScrn.hpp"
#include "mainScrn.hpp"
#include "screen.hpp"
#include "button.hpp"
class mainScrn:public screen{
    private:
    Button *playButton;
    Button *songsButton;
    Button *playerButton;
    Button *exitButton;
    public:
    mainScrn(){
        playerButton = new Button("player",{rectPos+20,screenHeight/2-50},font_height,font);
        playButton = new Button("playlist",{rectPos+20,screenHeight/2},font_height,font);
        songsButton = new Button("song list",{rectPos+20,screenHeight/2+50},font_height,font);
        exitButton = new Button("exit",{rectPos+20,screenHeight/2+100},font_height,font);
    }
    ~mainScrn(){
        delete playButton;
        delete songsButton;
        delete playerButton;
        delete exitButton;
    }
    static void playButtonFunc(){
        s=screens::playscrn;
    }
    static void songsButtonFunc(){
        s=screens::songsscrn;
    }
    static void playerButtonFunc(){
        s=screens::playerscrn;
    }
    static void exitButtonFunc(){
        isClosed=true;
    }
    void display(){
        UpdateMusicStream(music);
        playButton->Draw(playButtonFunc);
        playerButton->Draw(playerButtonFunc);
        songsButton->Draw(songsButtonFunc);
        exitButton->Draw(exitButtonFunc);
    }
};