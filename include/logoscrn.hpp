#pragma once
#include "logoScrn.hpp"
#include "mainScrn.hpp"
#include "screen.hpp"
#include "button.hpp"
//remove button and add welcome fadeing text and a timer to go to main screen
class logoScrn: public screen{
    private:
    //needed the pointer because font wasnt loading properly
    Button *mainButton;
    public:
    logoScrn(){
        //its not in render() so that it dosent render again and again and again
        mainButton = new Button("start",{screenWidth/2-24,screenHeight/2+100},font_height,font);
    }
    ~logoScrn(){
        delete mainButton;
    }
    //static function passed for error "void (mainScrn::*)()" is incompatible with parameter of type "void (*)()"
    static void mainButtonFunc(){
        s=screens::mainscrn;
    }
    void display(){
        mainButton->Draw(mainButtonFunc);
    }
};