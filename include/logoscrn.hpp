#pragma once
#include "screen.hpp"
class logoScrn:public screen{
    private:
    Texture2D texture;
    //needed the pointer because font wasnt loading properly
    Button *logoButton;
    public:
    logoScrn(){
        texture=LoadTexture("../resources/title.png");
        //its not in render() so that it dosent render again and again and again
        logoButton = new Button("logo",{400,100},32);
    }
    ~logoScrn(){
        delete logoButton;
        UnloadTexture(texture);
    }
    //static function passed for error "void (mainScrn::*)()" is incompatible with parameter of type "void (*)()"
    static void nextButton(){
        std::cout<<"hello"<<std::endl;
    }
    void display(){
        DrawTextureV(texture,{0,0},RAYWHITE);
        logoButton->Draw(nextButton);
    }
};