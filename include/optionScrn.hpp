#pragma once
#include "mainScrn.hpp"
#include "optionScrn.hpp"
#include "screen.hpp"
#include "button.hpp"

//color scheme
//font size
//volume
class optionScrn: public screen{
    private:
    Button *mainButton;
    Button *volumeButton;
    Button *fontSizeButton;
    Button *colorButton;
    static float posY;
    static float pos1X;
    static float pos2X;
    //for already clicked
    static int clicked1;
    static int clicked2;
    static int clicked3;
    static float length_of_bar;
    static Rectangle rect1;
    static Rectangle rect2;

    public:
    optionScrn(){
        optionScrn::length_of_bar=300;
        posY=screenHeight/2-50;
        pos1X=rectPos+250;
        pos2X=rectPos+250;
        clicked1=0;
        clicked2=0;
        clicked3=0;
        mainButton = new Button("back",{rectPos+20,screenHeight-10},font_height,font);
        volumeButton = new Button("volume",{rectPos+20,screenHeight/2-50},font_height,font);
        fontSizeButton = new Button("font size",{rectPos+20,screenHeight/2},font_height,font);
        colorButton = new Button("color pallet",{rectPos+20,screenHeight/2+50},font_height,font);
    }
    ~optionScrn(){
        delete mainButton;
        delete volumeButton;
        delete fontSizeButton;
        delete colorButton;
    }
    static void mainButtonFunc(){
        s=screens::mainscrn;
    }
    static void fontSizeButtonFunc(){
    }
    static void colorButtonFunc( ){
    }
    static void volumeButtonFunc( ){
        if(clicked1 % 2){
            rect1={pos1X,posY,length_of_bar,5};
            rect2={pos2X,posY,5,10};
            Vector2 mousePos=GetMousePosition();
            if(CheckCollisionPointRec(mousePos,rect1)){
                DrawRectangleRec(rect1,GRAY);
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    pos2X=GetMousePosition().x;
                    SetMasterVolume(pos2X/length_of_bar);
                }
                if(CheckCollisionPointRec(mousePos,rect2)){
                    DrawRectangleRec(rect2,BLACK);
                    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                        pos2X=GetMousePosition().x;
                        SetMasterVolume(pos2X/length_of_bar);
                    }
                }
                else{
                    DrawRectangleRec(rect2,GRAY);
                }

            }
            else{
                DrawRectangleRec(rect1,LIGHTGRAY);
                DrawRectangleRec(rect2,GRAY);
            }
        }
        clicked1++;
    }
    void display(){
        UpdateMusicStream(music);
        mainButton->Draw(mainButtonFunc);
        volumeButton->Draw2(volumeButtonFunc);
        fontSizeButton->Draw2(fontSizeButtonFunc);
        colorButton->Draw2(colorButtonFunc);

    }
};