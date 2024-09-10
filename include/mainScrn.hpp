#pragma once
#include "raylib.h"
#include "button.hpp"
class mainScrn{
    private:
    Texture2D texture;
    public:
    mainScrn(){
        //texture=LoadTexture("../resources/title.png");
    }
    ~mainScrn(){
        //UnloadTexture(texture);
    }
    static void pButton(){
        std::cout<<"hello"<<std::endl;
    }
    void render(){
        //DrawTextureV(texture,{0,0},RAYWHITE);
        Button playerButton("player",{400,100},32);
        //static function passed for error "void (mainScrn::*)()" is incompatible with parameter of type "void (*)()"
        playerButton.Draw(pButton);
    }
};