//
// Created by Iordan Tonchev on 9.10.21.
//
#include "include/gameLoop.h"
#include "Core/GameEngineCore.h"
#include "Managers/EventManager.h"
#include "utils/defines.h"
#include "Timers/Timers.h"
#include "Actors/PlayerCharacter.h"

BOOL gameLoop() {

    //FIXME MOVE LOOP INSIDE GAME ENGINE and implement the renderer game loop clear/update/present
    BOOL isRunning = TRUE;
    uint32_t ElapsedTime=0;
    float DeltaTime = 0.0f;
    playerActor *Player = NONE;
    initPlayerActor(&Player, "John Doe");
    SDLLoader(Player);
    printf("The Player Name is %s and he runs at %.2f anim. speed \n",
           getPlayerName(Player), (double) getAnimationSpeed(getBaseChar(Player)));
    while (isRunning) {
        DeltaTime = getDeltaTime(&ElapsedTime);
        //TODO Process input for player, state machine sets state, then animator executes
        //For enemies, instead of input have state based on player location
        DrawGame(0, DeltaTime, getBaseChar(Player));
        playerEventHandler(&isRunning, Player);
    }
    deinitPlayerActor(&Player);
    SDLUnloader();

    return SUCCESS;
}