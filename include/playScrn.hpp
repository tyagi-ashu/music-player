#pragma once
#include "playScrn.hpp"
#include "mainScrn.hpp"
#include "screen.hpp"
#include "button.hpp"

class playScrn:public screen{
    private:
    //Texture2D texture;
    //needed the pointer because font wasnt loading properly
    Button *mainButton;
    public:
    playScrn(){
        //texture=LoadTexture("../resources/title.png");
        //its not in render() so that it dosent render again and again and again
        mainButton = new Button("playlist",{400,100},32);
    }
    ~playScrn(){
        //UnloadTexture(texture);
    }
    //static-- to access this function when there is no instance of this class and 'draw' is called 
    static void mainButtonFunc1(){
        s=screens::mainscrn;
        std::cout<<"hello"<<std::endl;
    }
    void display(){
        //DrawTextureV(texture,{0,0},RAYWHITE);
        mainButton->Draw(mainButtonFunc1);
    }
};