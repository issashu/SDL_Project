//
// Created by Iordan Tonchev on 9.10.21.
//
#include "include/gameLoop.h"
#include "game_engine/include/Core/GameEngineCore.h"
#include "game_engine/include/Managers/EventManager.h"
#include "utils/include/utils/defines.h"

BOOL gameLoop() {

    //FIXME MOVE LOOP INSIDE GAME ENGINE and implement the renderer game loop clear/update/present
    BOOL isRunning = TRUE;
    SDLLoader();
    while (isRunning) {
        DrawGame(0);
        eventHandler(&isRunning);
    }
    //SDLUnloader();

    return SUCCESS;
}