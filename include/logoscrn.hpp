#pragma once
#include "logoScrn.hpp"
#include "mainScrn.hpp"
#include "screen.hpp"
#include "scrnManager.hpp"
#include "button.hpp"
class logoScrn: public screen{
    private:
    Texture2D texture;
    //needed the pointer because font wasnt loading properly
    Button *mainButton;
    public:
    logoScrn(){
        texture=LoadTexture("../resources/title.png");
        //its not in render() so that it dosent render again and again and again
        mainButton = new Button("logo",{400,100},32);
    }
    ~logoScrn(){
        delete mainButton;
        UnloadTexture(texture);
    }
    //static function passed for error "void (mainScrn::*)()" is incompatible with parameter of type "void (*)()"
    static void mainButtonFunc(){
        mainScrn *ms;
        ms= new mainScrn();
        ScrnManager::LoadScrn(ms);
        std::cout<<"hello"<<std::endl;
    }
    void display(){

        DrawTextureV(texture,{0,0},RAYWHITE);
        mainButton->Draw(mainButtonFunc);
    }
};