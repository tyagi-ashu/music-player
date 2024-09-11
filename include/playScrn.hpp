#pragma once
#include "screen.hpp"

class playScrn:public screen{
    private:
    //Texture2D texture;
    //needed the pointer because font wasnt loading properly
    Button *playerButton;
    public:
    playScrn(){
        //texture=LoadTexture("../resources/title.png");
        //its not in render() so that it dosent render again and again and again
        playerButton = new Button("playlist",{400,100},32);
    }
    ~playScrn(){
        delete playerButton;
        //UnloadTexture(texture);
    }
    //static-- to access this function when there is no instance of this class and 'draw' is called 
    static void backButton(){
        std::cout<<"hello"<<std::endl;
    }
    void display(){
        //DrawTextureV(texture,{0,0},RAYWHITE);
        playerButton->Draw(backButton);
    }
};