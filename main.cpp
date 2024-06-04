//
//  main.cpp
//
//  Copyright � 2018 Compiled Creations Limited. All rights reserved. hjkhkj
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)

#include <iostream>

#define SDL_MAIN_HANDLED
#include <windows.h>
#include "Tetris.h"

#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <conio.h>      /* getch */ 

#elif __APPLE__

#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#pragma clang diagnostic pop

#endif

#include "./InfoJoc.h"
#include "./Partida.h"


int main(int argc, const char* argv[])
{
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);

    Screen pantalla(SCREEN_SIZE_X, SCREEN_SIZE_Y);
    pantalla.show();

    Tetris tetris;
    tetris.jugarPartida(pantalla);
    
    return 0;
}

