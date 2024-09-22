#pragma once
#include "logoScrn.hpp"
#include "mainScrn.hpp"
#include "screen.hpp"
#include "button.hpp"

class logoScrn: public screen{
    private:
    Button *mainButton;
    struct rectangles{
        int flip=0;
        float posX;
        float posY=GetScreenHeight()/2+40;
        float width=50;float height=0;
    }rec0,rec1,rec2,rec3,rec4,rec5,rec6,rec7,rec8;

    std::vector<Color> color_vec={LIGHTGRAY,GRAY,DARKGRAY,BLACK};

    public:
    logoScrn(){
        mainButton = new Button("start",{screenWidth/2-24,screenHeight/2+100},font_height,font);
        
        rec0.posX=rectPos+200;
        rec1.posX=rectPos+250;
        rec2.posX=rectPos+300;
        rec3.posX=rectPos+350;
        rec4.posX=rectPos+400;
        rec5.posX=rectPos+450;
        rec6.posX=rectPos+500;
        rec7.posX=rectPos+550;
        rec8.posX=rectPos+600;
    }
    ~logoScrn(){
        delete mainButton;
    }
    static void mainButtonFunc(){
        s=screens::mainscrn;
    }
    void drawMusic(rectangles &rect,int h){
        Rectangle rec={rect.posX,rect.posY,rect.width,rect.height};
        DrawRectangleRec(rec,choose());
        DrawRectangleLinesEx(rec,0.3,BLACK);
        if(rect.flip==0){
            rect.posY-=3;rect.height+=3;
            if(rect.height>=h){
                rect.flip=1;
            }
        }
        if(rect.flip==1){
            rect.posY+=3;rect.height-=3;
            if(rect.height<=0){
                rect.flip=0;
            }
        }
    }
    Color choose(){
        int index=rand()% color_vec.size();
        Color name=color_vec[index];
        return name;
    }
    void display(){
        mainButton->Draw(mainButtonFunc);
        drawMusic(rec0,20);
        drawMusic(rec1,50);
        drawMusic(rec2,100);
        drawMusic(rec3,50);
        drawMusic(rec4,120);
        drawMusic(rec5,50);
        drawMusic(rec6,100);
        drawMusic(rec7,50);
        drawMusic(rec8,20);
    }
};