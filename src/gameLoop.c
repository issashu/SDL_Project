//
// Created by Iordan Tonchev on 9.10.21.
//
#include "include/gameLoop.h"
#include "Core/GameEngineCore.h"
#include "Managers/EventManager.h"
#include "utils/defines.h"
#include "Timers/Timers.h"

BOOL gameLoop() {

    //FIXME MOVE LOOP INSIDE GAME ENGINE and implement the renderer game loop clear/update/present
    BOOL isRunning = TRUE;
    uint32_t ElapsedTime=0;
    float DeltaTime = 0.0f;
    SDLLoader();
    while (isRunning) {
        DeltaTime = getDeltaTime(&ElapsedTime);
        //printf("%.3f\n", (double) DeltaTime);
        DrawGame(0, DeltaTime);
        eventHandler(&isRunning);
    }
    SDLUnloader();

    return SUCCESS;
}