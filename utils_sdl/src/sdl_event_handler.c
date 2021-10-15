//
// Created by Iordan Tonchev on 7.10.21.
//

#include <SDL_events.h>
#include "sdl_event_handler.h"
#include "sdl_gfx_renderer.h"

void eventHandler(BOOL *isRunning) {
    SDL_Event gameEvent;
    //TODO Unify everything in a single if statement and ||
    while (SDL_PollEvent(&gameEvent)) {
        if (gameEvent.key.type == SDL_KEYDOWN) {
            keyboardEvent(isRunning);
        }
        //TODO Disable mouse control for the end game
        if (gameEvent.button.type == SDL_MOUSEBUTTONDOWN) {
            *isRunning = FALSE;
        }

        if (gameEvent.cbutton.type == SDL_CONTROLLERBUTTONDOWN) {
            *isRunning = FALSE;
        }
    }
}

void keyboardEvent(BOOL *isRunning) {
    //TODO ADD DOXYGEN and set some default key event (also might be having slight delay because of pump
    // https://cpp.hotexamples.com/examples/-/-/SDL_GetKeyboardState/cpp-sdl_getkeyboardstate-function-examples.html
    SDL_PumpEvents();
    const Uint8 *gameKeyStates = SDL_GetKeyboardState(NULL);
    if(gameKeyStates[SDL_SCANCODE_UP]) {
        printf("UP ARROW is pressed.\n");
        return;
    }
    if(gameKeyStates[SDL_SCANCODE_RIGHT]) {
        printf("RIGHT ARROW is pressed.\n");
        return;
    }
    if(gameKeyStates[SDL_SCANCODE_DOWN]){
        printf("DOWN ARROW is pressed.\n");
        return;
    }
    if(gameKeyStates[SDL_SCANCODE_LEFT]) {
        printf("LEFT ARROW is pressed.\n");
        return;
    }
    if(gameKeyStates[SDL_SCANCODE_ESCAPE]){
        *isRunning = FALSE;
        return;
    }
    else{
        printf("Some random key pressed!\n");
        return;
    }
}