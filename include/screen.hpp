#pragma once
#include "raylib.h"

//needed for pointers to different screens
// so that i dont have to load entire app data all at once and delete previous screen data is possible
class screen{
    public:
    //virtual-- so that while destructing diff screens using this class, no undefined behaviour dont occur
    virtual ~screen(){};    
    virtual void display(){};
};
enum class screens{
    logoscrn,
    mainscrn,
    playscrn,
    null
};

screens s;
