//
// Created by Iordan Tonchev on 7.10.21.
//

#include <SDL_events.h>
#include "Managers/EventManager.h"
#include "Core/GameEngineCore.h"
#include "Actors/PlayerCharacter.h"
#include "utils/defines.h"
#include "Timers/Timers.h"

void keyboardEvent(BOOL *isRunning, playerActor *Player, const u_int8_t *gameKeyStates, float *DeltaTime,
                   SDL_Renderer **GfxRenderer, SDL_Texture **Texture);


void playerEventHandler(BOOL *isRunning, playerActor *Player, float *DeltaTime, SDL_Renderer **GfxRenderer,
                        SDL_Texture **Texture) {
    SDL_Event gameEvent;

    if (!SDL_PollEvent(&gameEvent)) {
        DrawCharacter(IDLE_STATE, DeltaTime, getBaseChar(Player), GfxRenderer, Texture);
    }
    while (SDL_PollEvent(&gameEvent)) {
        switch (gameEvent.type) {
            case SDL_QUIT:
                *isRunning = FALSE;
                break;

            case SDL_KEYDOWN:
                keyboardEvent(isRunning, Player, NULL, DeltaTime, GfxRenderer, Texture);
                break;

            case SDL_KEYUP:
                break;

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEWHEEL:
            case SDL_MOUSEWHEEL_FLIPPED:
            case SDL_MOUSEWHEEL_NORMAL:
                break;

            default:
                break;
        }
    }
}

void keyboardEvent(BOOL *isRunning, playerActor *Player, const u_int8_t *gameKeyStates, float *DeltaTime,
                   SDL_Renderer **GfxRenderer, SDL_Texture **Texture) {
    //TODO ADD DOXYGEN and set some default key event (also might be having slight delay because of pump
    //TODO Find a way to automate indexing. Maybe object struct should know the index of its texture
    // https://cpp.hotexamples.com/examples/-/-/SDL_GetKeyboardState/cpp-sdl_getkeyboardstate-function-examples.html
    static Vector2D Force;
    static Vector2D Friction;
    initVector2D(&Force);
    initVector2D(&Friction);
    gameKeyStates = SDL_GetKeyboardState(NULL);

    while (gameKeyStates[SDL_SCANCODE_UP]) {
        setState(getBaseChar(Player), JUMPING_UP);
        Force.set(&Force, 0.0, -2.0);
        moveCharacter(getBaseChar(Player), DeltaTime, &Force, &Friction);
        DrawCharacter(SDL_SCANCODE_UP, DeltaTime, getBaseChar(Player), GfxRenderer, Texture);
        SDL_PumpEvents();
    }
    while (gameKeyStates[SDL_SCANCODE_UP] && gameKeyStates[SDL_SCANCODE_RIGHT]) {
        setState(getBaseChar(Player), JUMPING_RIGHT);
        moveCharacter(getBaseChar(Player), DeltaTime, &Force, &Friction);
        DrawCharacter(SDL_SCANCODE_UP, DeltaTime, getBaseChar(Player), GfxRenderer, Texture);
        SDL_PumpEvents();
    }
    while (gameKeyStates[SDL_SCANCODE_UP] && gameKeyStates[SDL_SCANCODE_LEFT]) {
        setState(getBaseChar(Player), JUMPING_LEFT);
        moveCharacter(getBaseChar(Player), DeltaTime, &Force, &Friction);
        DrawCharacter(SDL_SCANCODE_UP, DeltaTime, getBaseChar(Player), GfxRenderer, Texture);
        SDL_PumpEvents();
    }
    while (gameKeyStates[SDL_SCANCODE_RIGHT]) {
        setState(getBaseChar(Player), RUNNING_RIGHT);
        Force.set(&Force, 2.0, 0.0);
        moveCharacter(getBaseChar(Player), DeltaTime, &Force, &Friction);
        DrawCharacter(SDL_SCANCODE_RIGHT, DeltaTime, getBaseChar(Player), GfxRenderer, Texture);
        SDL_PumpEvents();
    }
    while (gameKeyStates[SDL_SCANCODE_LEFT]) {
        setState(getBaseChar(Player), RUNNING_LEFT);
        Force.set(&Force, -2.0, 0.0);
        moveCharacter(getBaseChar(Player), DeltaTime, &Force, &Friction);
        DrawCharacter(SDL_SCANCODE_LEFT, DeltaTime, getBaseChar(Player), GfxRenderer, Texture);
        SDL_PumpEvents();
    }
    while (gameKeyStates[SDL_SCANCODE_DOWN]) {
        setState(getBaseChar(Player), CROUCHING);
        Force.set(&Force, 0.0, 2.0);
        moveCharacter(getBaseChar(Player), DeltaTime, &Force, &Friction);
        DrawCharacter(SDL_SCANCODE_DOWN, DeltaTime, getBaseChar(Player), GfxRenderer, Texture);
        SDL_PumpEvents();
    }
    while (gameKeyStates[SDL_SCANCODE_DOWN] && gameKeyStates[SDL_SCANCODE_RIGHT]) {
        setState(getBaseChar(Player), CRAWLING_RIGHT);
        moveCharacter(getBaseChar(Player), DeltaTime, &Force, &Friction);
        DrawCharacter(SDL_SCANCODE_DOWN, DeltaTime, getBaseChar(Player), GfxRenderer, Texture);
        SDL_PumpEvents();
    }
    while (gameKeyStates[SDL_SCANCODE_DOWN] && gameKeyStates[SDL_SCANCODE_LEFT]) {
        setState(getBaseChar(Player), CRAWLING_LEFT);
        moveCharacter(getBaseChar(Player), DeltaTime, &Force, &Friction);
        DrawCharacter(SDL_SCANCODE_DOWN, DeltaTime, getBaseChar(Player), GfxRenderer, Texture);
        SDL_PumpEvents();
    }
    while (gameKeyStates[SDL_SCANCODE_ESCAPE]) {
        *isRunning = FALSE;
        SDL_PumpEvents();
    }
}