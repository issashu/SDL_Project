//
// Created by Iordan Tonchev on 7.10.21.
//

#include <SDL.h>
#include <SDL_events.h>
#include "sdl_event_handler.h"


void eventHandler(BOOL *quit) {
    SDL_Event gameEvent;
    //TODO Unify everything in a single if statement and ||
    while (SDL_PollEvent(&gameEvent)) {
        if (gameEvent.key.type == SDL_KEYDOWN) {
            *quit = TRUE;
        }
        //TODO Disable mouse control for the end game
        if (gameEvent.button.type == SDL_MOUSEBUTTONDOWN) {
            *quit = TRUE;
        }

        if (gameEvent.cbutton.type == SDL_CONTROLLERBUTTONDOWN) {
            *quit = TRUE;
        }
    }
}
