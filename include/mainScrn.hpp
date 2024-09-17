#pragma once
#include "playScrn.hpp"
#include "songsScrn.hpp"
#include "playerScrn.hpp"
#include "optionScrn.hpp"
#include "mainScrn.hpp"
#include "screen.hpp"
#include "button.hpp"
class mainScrn:public screen{
    private:
    //needed the pointer because font wasnt loading properly
    Button *playButton;
    Button *songsButton;
    Button *playerButton;
    Button *optionButton;
    public:
    mainScrn(){
        //its not in render() so that it dosent render again and again and again
        playerButton = new Button("player",{rectPos+20,screenHeight/2-50},font_height,font);
        playButton = new Button("playlist",{rectPos+20,screenHeight/2},font_height,font);
        songsButton = new Button("song list",{rectPos+20,screenHeight/2+50},font_height,font);
        optionButton = new Button("options",{rectPos+20,screenHeight/2+100},font_height,font);
    }
    ~mainScrn(){
        delete playButton;
        delete songsButton;
        delete playerButton;
        delete optionButton;
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
    static void optionButtonFunc(){
        s=screens::optionscrn;
    }
    void display(){
        UpdateMusicStream(music);
        playButton->Draw(playButtonFunc);
        playerButton->Draw(playerButtonFunc);
        songsButton->Draw(songsButtonFunc);
        optionButton->Draw(optionButtonFunc);
    }
};