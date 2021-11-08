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
    SDLLoader();
    playerActor *Player = NONE;
    Player = initPlayerActor(Player, 0, "John Doe");
    setPlayerName(Player, "Issashu");
    setAnimationSpeed(Player, 150);
    printf("The Player Name is %s and he runs at %d anim. speed \n",
           getPlayerName(Player), getAnimationSpeed(Player));
    while (isRunning) {
        DeltaTime = getDeltaTime(&ElapsedTime);
        //TODO Process input for player, state machine sets state, then animator executes
        //For enemies, instead of input have state based on player location
        //DrawGame(0, DeltaTime);
        playerEventHandler(&isRunning, NULL);
    }
    deinitPlayerActor(Player);
    SDLUnloader();

    return SUCCESS;
}