#pragma once
#include "playScrn.hpp"
#include "mainScrn.hpp"
#include "screen.hpp"
#include "scrnManager.hpp"
#include "button.hpp"
class mainScrn:public screen{
    private:
    //Texture2D texture;
    //needed the pointer because font wasnt loading properly
    Button *playButton;
    public:
    mainScrn(){
        //texture=LoadTexture("../resources/title.png");
        //its not in render() so that it dosent render again and again and again
        playButton = new Button("main",{400,100},32);
    }
    ~mainScrn(){
        delete playButton;
        //UnloadTexture(texture);
    }
    //static function passed for error "void (mainScrn::*)()" is incompatible with parameter of type "void (*)()"
    static void playButtonFunc(){
        playScrn *ps;
        ps= new playScrn();
        ScrnManager::LoadScrn(ps);
        std::cout<<"hello"<<std::endl;
    }
    void display(){
        //DrawTextureV(texture,{0,0},RAYWHITE);
        playButton->Draw(playButtonFunc);
    }
};