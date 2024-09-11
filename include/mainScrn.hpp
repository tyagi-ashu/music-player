#pragma once
#include "screen.hpp"
class mainScrn:public screen{
    private:
    //Texture2D texture;
    //needed the pointer because font wasnt loading properly
    Button *mainButton;
    public:
    mainScrn(){
        //texture=LoadTexture("../resources/title.png");
        //its not in render() so that it dosent render again and again and again
        mainButton = new Button("main",{400,100},32);
    }
    ~mainScrn(){
        delete mainButton;
        //UnloadTexture(texture);
    }
    //static function passed for error "void (mainScrn::*)()" is incompatible with parameter of type "void (*)()"
    static void backButton(){
        std::cout<<"hello"<<std::endl;
    }
    void display(){
        //DrawTextureV(texture,{0,0},RAYWHITE);
        mainButton->Draw(backButton);
    }
};