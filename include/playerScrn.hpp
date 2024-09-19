#pragma once
#include "playerScrn.hpp"
#include "mainScrn.hpp"
#include "screen.hpp"
#include "button.hpp"
#include "playlist.hpp"
//play prev

class playerScrn:public screen{
    private:
    Button *mainButton;

    bool playNext=false;
    bool playPrev=false;
    float volume=0.5;
    float second=0;
    bool play=false;
    struct bar{
        float length_of_bar;
        Rectangle rect1;
        Rectangle rect2;
        bool collision=false;
        float posY;
        float pos1X;
        float pos2X;
        //use=0 for volume bar, use =1 for seek bar
        int use;
    }volBar,seekBar;

    struct rectangles{
        int flip=0;
        float posX;
        float posY=GetScreenHeight()/2;
        float width=8;float height=0;
    }rec0,rec1,rec2,rec3,rec4,rec5,rec6,rec7,rec8;

    public:
    playerScrn(){
        mainButton = new Button("back",{rectPos+20,screenHeight-10},font_height,font);
        volBar.length_of_bar=200;
        volBar.pos1X=screenWidth/2+160;
        volBar.pos2X=volBar.pos1X+volBar.length_of_bar/2;
        volBar.posY=screenHeight/2+230;
        volBar.use=0;

        seekBar.length_of_bar=screenWidth-(rectPos+25);
        seekBar.pos1X=rectPos+30;
        seekBar.pos2X=seekBar.pos1X;
        seekBar.posY=screenHeight/2+140;
        seekBar.use=1;

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
    ~playerScrn(){
        delete mainButton;
    }
    static void mainButtonFunc(){
        s=screens::mainscrn;
    }
    void drawMusic(rectangles &rect,int h){
        DrawRectangle(rect.posX,rect.posY,rect.width,rect.height,GRAY);
        if(rect.flip==0){
            rect.posY-=1.5;rect.height+=3;
            if(rect.height>=h){
                rect.flip=1;
            }
        }
        if(rect.flip==1){
            rect.posY+=1.5;rect.height-=3;
            if(rect.height<=0){
                rect.flip=0;
            }
        }
    }
    void addBar(bar &b,Vector2 mousePos,float &volume,float& timePos){
        b.rect1={b.pos1X,b.posY,b.length_of_bar,5};
        b.rect2={b.pos2X,b.posY,5,10};
        if(b.use){
            b.pos2X=(timePos*b.length_of_bar/GetMusicTimeLength(music))+b.pos1X;
        }
        if(CheckCollisionPointRec(mousePos,b.rect1)){
            DrawRectangleRec(b.rect1,GRAY);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                b.pos2X=mousePos.x;
                if(b.use){
                    timePos=(b.pos2X-b.pos1X)*GetMusicTimeLength(music)/b.length_of_bar;
                    SeekMusicStream(music,timePos );
                }
                else{
                    volume=(b.pos2X-b.pos1X)/b.length_of_bar;
                    SetMusicVolume(music,volume);
                }
            }
            if(CheckCollisionPointRec(mousePos,b.rect2)){
                if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                    b.collision=true;
                }
            }
            if(b.collision){
                DrawRectangleRec(b.rect2,RED);
                if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                b.pos2X=mousePos.x;
                if(b.use){
                    timePos=(b.pos2X-b.pos1X)*GetMusicTimeLength(music)/b.length_of_bar;
                    SeekMusicStream(music,timePos );
                }
                else{
                    volume=(b.pos2X-b.pos1X)/b.length_of_bar;
                    SetMusicVolume(music,volume);
                }
                }
            }
            else{
                DrawRectangleRec(b.rect2,GRAY);
            }

        }
        else{
            DrawRectangleRec(b.rect1,LIGHTGRAY);
            DrawRectangleRec(b.rect2,GRAY);
        }

    }
    void display(){
        UpdateMusicStream(music);
        mainButton->Draw(mainButtonFunc);
        float posY=screenHeight/2+200;
        Vector2 mousePos=GetMousePosition();

        float posX=screenWidth/2-110;
        float font2_width=MeasureTextEx(font2,"B",font2_height,0).x;
        DrawRectangleLines(rectPos+30,posY-20,screenWidth-(rectPos+25),font2_height+20,BLACK);
        if(mousePos.x>posX && mousePos.x<posX+font2_width && mousePos.y>posY && mousePos.y<posY+font2_height){
            DrawTextEx(font2,"B",{posX, posY},font2_height,0,RED);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                playPrev=true;
                playNext=false;
                play=true;
            }
        }
        else{
            DrawTextEx(font2,"B",{posX,posY},font2_height,0,BLACK);
        }

        posX=screenWidth/2;
        font2_width=MeasureTextEx(font2,"Q",font2_height,0).x;
        if(mousePos.x>posX && mousePos.x<posX+font2_width && mousePos.y>posY && mousePos.y<posY+font2_height){
            DrawTextEx(font2,"Q",{posX, posY},font2_height,0,RED);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsMusicStreamPlaying(music)){
                play=false;
            }
            if(p.count!=0 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !IsMusicStreamPlaying(music)){
                play=true;
            }
        }
        else{
            DrawTextEx(font2,"Q",{posX,posY},font2_height,0,BLACK);
        }

        posX=screenWidth/2+80;
        font2_width=MeasureTextEx(font2,"A",font2_height,0).x;
        if(mousePos.x>posX && mousePos.x<posX+font2_width && mousePos.y>posY && mousePos.y<posY+font2_height){
            DrawTextEx(font2,"A",{posX, posY},font2_height,0,RED);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                playNext=true;
                playPrev=false;
                play=true;
            }
        }
        else{
            DrawTextEx(font2,"A",{posX,posY},font2_height,0,BLACK);
        }

        if(p.count!=0 && play && ((playPrev||playNext) || !IsMusicReady(music))){
            string path;
            if(playNext || (play && !playNext && !playPrev)){
                path=p.get_path(true);
            }
            else if(playPrev){
                path=p.get_path(false);
            }
            music = LoadMusicStream(path.c_str());
            SetMusicVolume(music,volume);
            PlayMusicStream(music);
            second=0;
        }
        else if(p.count!=0 &&  play && IsMusicReady(music)){
            ResumeMusicStream(music);
        }
        else if(p.count!=0 &&  !play && IsMusicReady(music)){
            PauseMusicStream(music);
        }
        if(IsMusicReady(music)){
            second=GetMusicTimePlayed(music);
            addBar(seekBar,mousePos,volume,second);
            const char* text=TextToLower((p.currsong->next->p.second).c_str());
            DrawTextEx(font,text,{screenWidth/2 - MeasureTextEx(font,text,font_height,0).x/2 + rectPos,screenHeight/2-120},font_height,0,GRAY);
        }
        if(GetMusicTimeLength(music)!=0){
            float timePlayed = GetMusicTimePlayed(music)/GetMusicTimeLength(music);
            if (timePlayed > 0.995f) timePlayed = 1.0f;
            if(timePlayed==1.0f){
                playNext=true;
                playPrev=false;
                StopMusicStream(music);
            }
            else{
                playNext=false;
                playPrev=false;
            }
        }
        else{
            playPrev=false;
            playNext=false;
            play=false;
        }
        if(IsMusicStreamPlaying(music)){
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
        DrawTextEx(font,"volume :",{screenWidth/2+160,posY},font_height-10,2,BLACK);
        addBar(volBar,mousePos,volume,second);
    }
};