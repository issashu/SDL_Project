//
// Created by Iordan Tonchev on 7.10.21.
//

#include <SDL_events.h>
#include "Physics/sdl_vector2D.h"
#include "Core/sdl_event_handler.h"
#include "Core/sdl_command.h"
#include "Graphics/sdl_gfx_renderer.h"

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
        Vector2D vec1, vec2;
        initVector2D(&vec1);
        initVector2D(&vec2);
        vec1.print(&vec1);
        vec2.print(&vec2);
        SDL_PumpEvents();
    }
    while(gameKeyStates[SDL_SCANCODE_ESCAPE]){
        *isRunning = FALSE;
        SDL_PumpEvents();
        break;
    }
    SDLdrawGame(KEY_PRESS_SURFACE_DEFAULT);
}