#pragma once
#include "screen.hpp"
#include "logoScrn.hpp"
#include "mainScrn.hpp"
#include "playScrn.hpp"
#include "scrnManager.hpp"
class scrnManager{
    private:
    static screen* nextState;
    static screens s;
    public:
    static void changeScrn(screens){
        switch(s){
            case screens::logoscrn:
            nextState=new logoScrn();
            break;
            case screens:: mainscrn:
            nextState=new mainScrn();
            break;
            case screens:: playscrn:
            nextState=new playScrn();
            break;
            case screens:: null:
            std::cout<<"nothing selected"<<std::endl;
            break;
        }
        nextState->display();
    }
};