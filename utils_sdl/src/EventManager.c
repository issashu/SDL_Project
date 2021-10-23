//
// Created by Iordan Tonchev on 7.10.21.
//

#include <SDL_events.h>
#include "Managers/EventManager.h"
#include "Core/GameEngineCore.h"
#include "Graphics/sdl_gfx_renderer.h"

void eventHandler(BOOL *isRunning) {
    SDL_Event gameEvent;
    while (SDL_PollEvent(&gameEvent)) {
        switch(gameEvent.type){
            case SDL_QUIT:
                *isRunning = FALSE;
                break;

            case SDL_KEYDOWN:
                keyboardEvent(isRunning);
                break;

//TODO Disable mouse control for the end game
            case SDL_MOUSEBUTTONDOWN:
                *isRunning = FALSE;
        }
    }
}

void keyboardEvent(BOOL *isRunning) {
    //TODO ADD DOXYGEN and set some default key event (also might be having slight delay because of pump
    // https://cpp.hotexamples.com/examples/-/-/SDL_GetKeyboardState/cpp-sdl_getkeyboardstate-function-examples.html
    SDL_PumpEvents();
    const Uint8 *gameKeyStates = SDL_GetKeyboardState(NULL);
    while(gameKeyStates[SDL_SCANCODE_UP]) {
        SDLdrawGame(KEY_PRESS_SURFACE_UP);
        printf("UP ARROW is pressed.\n");
        SDL_PumpEvents();
    }
    while(gameKeyStates[SDL_SCANCODE_RIGHT]) {
        SDLdrawGame(KEY_PRESS_SURFACE_RIGHT);
        printf("RIGHT ARROW is pressed.\n");
        SDL_PumpEvents();
    }
    while(gameKeyStates[SDL_SCANCODE_DOWN]){
        SDLdrawGame(KEY_PRESS_SURFACE_DOWN);
        printf("DOWN ARROW is pressed.\n");
        SDL_PumpEvents();
    }
    while(gameKeyStates[SDL_SCANCODE_LEFT]) {
        SDLdrawGame(KEY_PRESS_SURFACE_LEFT);
        printf("LEFT ARROW is pressed.\n");
        SDL_PumpEvents();
    }
    while(gameKeyStates[SDL_SCANCODE_SPACE]){
        printf("SPACE is pressed.\n");
    }
    while(gameKeyStates[SDL_SCANCODE_ESCAPE]){
        *isRunning = FALSE;
        SDL_PumpEvents();
        break;
    }
    SDLdrawGame(KEY_PRESS_SURFACE_DEFAULT);
}