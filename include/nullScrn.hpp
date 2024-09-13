#pragma once
#include "screen.hpp"
class nullScrn:public screen{
    private:
    public:
    nullScrn(){
    }
    ~nullScrn(){
        //UnloadTexture(texture);
    }
    void display(){
        
    }
};