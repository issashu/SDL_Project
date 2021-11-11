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
#include "Managers/TextureManager.h"

BOOL mainGame() {

    //FIXME MOVE LOOP INSIDE GAME ENGINE TO RESTORE ENCAPSULATION
    BOOL isRunning = TRUE;
    uint32_t ElapsedTime=0;
    float DeltaTime = 0.0f;
    playerActor *Player = NONE;
    Camera *MainCamera = NONE;
    SDL_Window *AppWindow = NONE;
    SDL_Renderer *GfxRenderer = NONE;
    SDL_Texture *Texture = NONE;
    initPlayerActor(&Player, "John Doe");
    initCamera2D(&MainCamera);
    SDLLoader(Player, &GfxRenderer, &AppWindow);

    while (isRunning) {
        DeltaTime = getDeltaTime(&ElapsedTime);
        DrawCamera(MainCamera, &GfxRenderer);
        playerEventHandler(&isRunning, Player, &DeltaTime, &GfxRenderer, &Texture);
        //enemyEventHandler();
        //TODO Add texture to character and camera, so they can be separately destroyed
    }
    deinitPlayerActor(&Player);
    deinitCamera2D(&MainCamera);
    SDLUnloader(GfxRenderer, AppWindow, NULL);

    return SUCCESS;
}