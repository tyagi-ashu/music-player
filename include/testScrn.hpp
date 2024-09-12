#pragma once
#include "testScrn.hpp"
#include "mainScrn.hpp"
#include "screen.hpp"
#include "scrnManager.hpp"
#include "button.hpp"

class testScrn:public screen{
    private:
    //Texture2D texture;
    //needed the pointer because font wasnt loading properly
    Button *mainButton;
    public:
    testScrn(){
        //texture=LoadTexture("../resources/title.png");
        //its not in render() so that it dosent render again and again and again
        mainButton = new Button("playlist",{400,100},32);
    }
    ~testScrn(){
        //UnloadTexture(texture);
    }
    //static-- to access this function when there is no instance of this class and 'draw' is called 
    static void mainButtonFunc(){
        mainScrn *ms;
        ms= new mainScrn();
        ScrnManager::LoadScrn(ms);
        std::cout<<"hello"<<std::endl;
    }
    void display(){
        //DrawTextureV(texture,{0,0},RAYWHITE);
        mainButton->Draw(mainButtonFunc);
    }
};