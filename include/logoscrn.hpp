#pragma once
#include "logoScrn.hpp"
#include "mainScrn.hpp"
#include "screen.hpp"
#include "button.hpp"
//remove button and add welcome fadeing text and a timer to go to main screen
class logoScrn: public screen{
    private:
    Texture2D texture;
    //needed the pointer because font wasnt loading properly
    Button *mainButton;
    Font font;
    int font_height=24;
    public:
    logoScrn(){
        texture=LoadTexture("../resources/title.png");
        font=LoadFontEx("../resources/my-font.ttf",font_height,NULL,0);
        //its not in render() so that it dosent render again and again and again
        mainButton = new Button("LOGO",{400,100},font_height,font);
    }
    ~logoScrn(){
        delete mainButton;
        UnloadTexture(texture);
    }
    //static function passed for error "void (mainScrn::*)()" is incompatible with parameter of type "void (*)()"
    static void mainButtonFunc(){
        s=screens::mainscrn;
    }
    void display(){

        DrawTextureV(texture,{0,0},RAYWHITE);
        mainButton->Draw(mainButtonFunc);
    }
};