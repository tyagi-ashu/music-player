#pragma once

#include "screen.hpp"

class ScrnManager
{
    public: 
        static void LoadScrn(screen* scrn1)
        {
            scrn = scrn1;
            isScrnLoaded = 1;
        };

        static void Update()
        {
            scrn->display();
        };

        static int ScrnLoaded()
        {
            return isScrnLoaded;
        };
    private: 
        inline static int isScrnLoaded;
        inline static screen *scrn;
};