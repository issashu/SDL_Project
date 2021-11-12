//
// Created by Iordan Tonchev on 9.10.21.
//

#include "Actors/PlayerCharacter.h"
#include "Core/Camera2D.h"
#include "Core/MainGameLoop.h"
#include "Core/GameEngineCore.h"
#include "Graphics/GraphicsRenderer2D.h"
#include "Managers/EventManager.h"
#include "utils/defines.h"
#include "Timers/Timers.h"


#include "Managers/TextureManager.h"

BOOL mainGame() {
    BOOL isRunning = TRUE;
    uint32_t ElapsedTime=0;
    float DeltaTime = 0.0f;
    playerActor *Player = NONE;
    Camera *MainCamera = NONE;
    SDL_Window *AppWindow = NONE;
    SDL_Renderer *GfxRenderer = NONE;
    initPlayerActor(&Player, "John Doe");
    initCamera2D(&MainCamera);
    SDLLoader(Player, &GfxRenderer, &AppWindow);

    while (isRunning) {
        DeltaTime = getDeltaTime(&ElapsedTime);
        clearRenderer(&GfxRenderer);
        //DrawParalaxBackground() method to sort out paralax backgrounds
        DrawCamera(MainCamera, &GfxRenderer, getCameraTexture(MainCamera));
        characterEventHandler(&isRunning, getBaseChar(Player), NONE);
        updateCharacterActor(getBaseChar(Player), &DeltaTime, &GfxRenderer,
                             getObjectTexture(getBaseObj(getBaseChar(Player))));
        //enemyEventHandler();
        presentRenderer(GfxRenderer);
        destroyTexture(getObjectTexture(getBaseObj(getBaseChar(Player))));
        destroyTexture(getCameraTexture(MainCamera));

        // Connected render to vsync and using delta time, so should have no effect
        SDL_Delay(1000/60);
    }
    deinitPlayerActor(&Player);
    deinitCamera2D(&MainCamera);
    SDLUnloader(GfxRenderer, AppWindow, NULL);

    return SUCCESS;
}