//
// Created by Iordan Tonchev on 7.10.21.
//

#include <SDL_events.h>
#include "Managers/EventManager.h"
#include "Core/GameEngineCore.h"
#include "Actors/PlayerCharacter.h"
#include "utils/defines.h"

void playerEventHandler(BOOL *isRunning, playerActor *Player) {
    SDL_Event gameEvent;
    const u_int8_t *gameKeyStates = SDL_GetKeyboardState(NULL);
    while (SDL_PollEvent(&gameEvent)) {
        switch(gameEvent.type){
            case SDL_QUIT:
                *isRunning = FALSE;
                break;
            case SDL_KEYDOWN:
                keyboardEvent(isRunning, Player, gameKeyStates);
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
                keyboardEvent(isRunning, Player, gameKeyStates);
        }
    }
}

void keyboardEvent(BOOL *isRunning, playerActor *Player, const u_int8_t *gameKeyStates) {
    //TODO ADD DOXYGEN and set some default key event (also might be having slight delay because of pump
    //TODO Find a way to automate indexing. Maybe object struct should know the index of its texture
    // https://cpp.hotexamples.com/examples/-/-/SDL_GetKeyboardState/cpp-sdl_getkeyboardstate-function-examples.html
    if (gameKeyStates[SDL_SCANCODE_UP]) {
        setState(getBaseChar(Player),JUMPING_UP);
        DrawGame(SDL_SCANCODE_UP, 0, getBaseChar(Player));
        printf("UP ARROW is pressed.\n");
    }
    if (gameKeyStates[SDL_SCANCODE_UP] && gameKeyStates[SDL_SCANCODE_RIGHT]) {
        setState(getBaseChar(Player),JUMPING_RIGHT);
        DrawGame(SDL_SCANCODE_RIGHT, 0, getBaseChar(Player));
        printf("RIGHT-UP ARROWS are pressed.\n");
    }
    if (gameKeyStates[SDL_SCANCODE_UP] && gameKeyStates[SDL_SCANCODE_LEFT]) {
        setState(getBaseChar(Player),JUMPING_LEFT);
        DrawGame(SDL_SCANCODE_RIGHT, 0, getBaseChar(Player));
        printf("LEFT-UP ARROWS are pressed.\n");
    }
    if (gameKeyStates[SDL_SCANCODE_RIGHT]) {
        setState(getBaseChar(Player),RUNNING_RIGHT);
        DrawGame(SDL_SCANCODE_RIGHT, 0, getBaseChar(Player));
        printf("RIGHT ARROW is pressed.\n");
    }
    if (gameKeyStates[SDL_SCANCODE_LEFT]) {
        setState(getBaseChar(Player),RUNNING_LEFT);
        DrawGame(SDL_SCANCODE_LEFT, 0, getBaseChar(Player));
        printf("LEFT ARROW is pressed.\n");
    }
    if (gameKeyStates[SDL_SCANCODE_DOWN]) {
        setState(getBaseChar(Player),CROUCHING);
        DrawGame(SDL_SCANCODE_DOWN, 0, getBaseChar(Player));
        printf("DOWN ARROW is pressed.\n");
    }
    if (gameKeyStates[SDL_SCANCODE_DOWN] && gameKeyStates[SDL_SCANCODE_RIGHT]){
        setState(getBaseChar(Player),CRAWLING_RIGHT);
        DrawGame(SDL_SCANCODE_DOWN, 0, getBaseChar(Player));
        printf("RIGHT - DOWN ARROWS are pressed.\n");
    }
    if (gameKeyStates[SDL_SCANCODE_DOWN] && gameKeyStates[SDL_SCANCODE_LEFT]){
        setState(getBaseChar(Player),CRAWLING_LEFT);
        DrawGame(SDL_SCANCODE_DOWN, 0, getBaseChar(Player));
        printf("LEFT - DOWN ARROWS are pressed.\n");
    }
    if (gameKeyStates[SDL_SCANCODE_ESCAPE]){
        *isRunning = FALSE;
    }
    //FIXME NEED A DEFAULT STATE IN THE MACHINE
}