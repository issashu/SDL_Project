//
// Created by Iordan Tonchev on 9.10.21.
//

#include "include/gameLoop.h"
BOOL gameLoop(){
    BOOL quit = FALSE;
    while(!quit){
        SDLdrawGame();
        eventHandler(&quit);
    }

    return SUCCESS;
}