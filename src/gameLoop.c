//
// Created by Iordan Tonchev on 9.10.21.
//
#include "include/gameLoop.h"
#include "utils_sdl/include/Core/GameEngineCore.h"
#include "utils_sdl/include/Managers/EventManager.h"
#include "utils/defines.h"

BOOL gameLoop() {

    SDLLoader();
    //FIXME MOVE LOOP INSIDE GAME ENGINE and implement the renderer game loop clear/update/present
    BOOL isRunning = TRUE;
    while (isRunning) {
        DrawGame(0);
        eventHandler(&isRunning);
    }
    //SDLUnloader();

    return SUCCESS;
}