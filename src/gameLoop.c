//
// Created by Iordan Tonchev on 9.10.21.
//

#include "include/gameLoop.h"
#include "Core/GameEngineCore.h"
#include "Managers/EventManager.h"
#include "utils/defines.h"
#include "Timers/Timers.h"
#include "Actors/PlayerCharacter.h"
#include "Core/Camera2D.h"
#include "Graphics/GraphicsRenderer2D.h"

BOOL gameLoop() {

    //FIXME MOVE LOOP INSIDE GAME ENGINE TO RESTORE ENCAPSULATION
    BOOL isRunning = TRUE;
    uint32_t ElapsedTime=0;
    float DeltaTime = 0.0f;
    playerActor *Player = NONE;
    Camera *MainCamera = NONE;
    SDL_Renderer *GfxRenderer = NONE;
    initPlayerActor(&Player, "John Doe");
    initCamera2D(&MainCamera);
    setCameraPosition(&MainCamera, &getObjRect(getBaseObj(getBaseChar(Player)))->x,
                                   &getObjRect(getBaseObj(getBaseChar(Player)))->y);
    SDLLoader(Player);

    while (isRunning) {
        DeltaTime = getDeltaTime(&ElapsedTime);
        playerEventHandler(&isRunning, Player, &DeltaTime);
        setCameraPosition(&MainCamera,&getObjRect(getBaseObj(getBaseChar(Player)))->x,
                                       &getObjRect(getBaseObj(getBaseChar(Player)))->y);
        //DrawCamera(MainCamera);
        //enemyEventHandler();
    }
    deinitPlayerActor(&Player);
    SDLUnloader();

    return SUCCESS;
}