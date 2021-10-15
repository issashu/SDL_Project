//
// Created by Iordan Tonchev on 9.10.21.
//
#include "include/gameLoop.h"

BOOL gameLoop(){

    SDLLoader();
    BOOL isRunning = TRUE;
    while(isRunning){
        SDLdrawGame();
        eventHandler(&isRunning);
    }
    SDLUnloader();

    return SUCCESS;
}