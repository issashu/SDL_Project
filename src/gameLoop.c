//
// Created by Iordan Tonchev on 9.10.21.
//
#include "include/gameLoop.h"
#include "sdl_command.h"
#include "sdl_event_handler.h"

BOOL gameLoop(){

    SDLLoader();
    BOOL quit = FALSE;
    while(!quit){
        SDLdrawGame();
        eventHandler(&quit);
    }
    SDLUnloader();

    return SUCCESS;
}