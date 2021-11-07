//
// Created by Iordan Tonchev on 7.10.21.
//

#include <SDL_events.h>
#include "Managers/EventManager.h"
#include "Core/GameEngineCore.h"
#include "utils/defines.h"

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
            case SDL_KEYUP:
                break;
//TODO Disable mouse control for the end game and fix the default idle state
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEWHEEL:
            case SDL_MOUSEWHEEL_FLIPPED:
            case SDL_MOUSEWHEEL_NORMAL:
                break;

            default:
                keyboardEvent(isRunning);
        }
    }
}

void keyboardEvent(BOOL *isRunning) {
    //TODO ADD DOXYGEN and set some default key event (also might be having slight delay because of pump
    //TODO Find a way to automate indexing. Maybe object struct should know the index of its texture
    // https://cpp.hotexamples.com/examples/-/-/SDL_GetKeyboardState/cpp-sdl_getkeyboardstate-function-examples.html
    SDL_PumpEvents();
    const Uint8 *gameKeyStates = SDL_GetKeyboardState(NULL);
    while (gameKeyStates[SDL_SCANCODE_UP]) {
        DrawGame(SDL_SCANCODE_UP, 0);
        printf("UP ARROW is pressed.\n");
        SDL_PumpEvents();
    }
    while (gameKeyStates[SDL_SCANCODE_RIGHT]) {
        DrawGame(SDL_SCANCODE_RIGHT, 0);
        printf("RIGHT ARROW is pressed.\n");
        SDL_PumpEvents();
    }
    while (gameKeyStates[SDL_SCANCODE_DOWN]){
        DrawGame(SDL_SCANCODE_DOWN, 0);
        printf("DOWN ARROW is pressed.\n");
        SDL_PumpEvents();
    }
    while (gameKeyStates[SDL_SCANCODE_LEFT]) {
        DrawGame(SDL_SCANCODE_LEFT, 0);
        printf("LEFT ARROW is pressed.\n");
        SDL_PumpEvents();
    }
    while (gameKeyStates[SDL_SCANCODE_SPACE]){
        DrawGame(SDL_SCANCODE_SPACE, 0);
        printf("SPACE is pressed.\n");
        SDL_PumpEvents();
    }
    while (gameKeyStates[SDL_SCANCODE_ESCAPE]){
        *isRunning = FALSE;
        break;
    }
    //FIXME NEED A DEFAULT STATE IN THE MACHINE
}