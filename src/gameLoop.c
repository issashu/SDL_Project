//
// Created by Iordan Tonchev on 9.10.21.
//
#include "include/gameLoop.h"

BOOL gameLoop(){

    SDLLoader();
    //FIXME FIX DEFINES AND MAGIC NUMBERS. UUsed 0 to avoid sdl_includes
    SDLdrawGame(0);
    BOOL isRunning = TRUE;
    while(isRunning){
        eventHandler(&isRunning);
    }
    SDLUnloader();

    return SUCCESS;
}