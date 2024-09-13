#pragma once
#include "raylib.h"
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
} s;
