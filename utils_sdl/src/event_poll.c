//
// Created by Iordan Tonchev on 7.10.21.
//

#include "event_poll.h"

int8_t eventHandler(SDL_Event** gameEvent){
    int8_t quit = FALSE;
    while (SDL_PollEvent(*gameEvent)){
        if((*gameEvent)->key.type == SDL_KEYDOWN){
            quit = TRUE;
        }
        if ((*gameEvent)->key.type == SDL_MOUSEBUTTONDOWN) {
            quit = TRUE;
        }
    }
    return quit;
}
