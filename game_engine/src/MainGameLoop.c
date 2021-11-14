//
// Created by Iordan Tonchev on 9.10.21.
//

#include "Actors/PlayerCharacter.h"
#include "Core/Camera2D.h"
#include "Core/MainGameLoop.h"
#include "Core/sdl_default_app_settings.h"
#include "Core/GameEngineCore.h"
#include "Graphics/GraphicsRenderer2D.h"
#include "Managers/EventManager.h"
#include "Managers/CollisionManager.h"
#include "utils/defines.h"
#include "Timers/Timers.h"
#include "Graphics/DrawParalaxBackgrounds.h"
#include "Managers/TextureManager.h"

BOOL mainGame() {
    BOOL isRunning = TRUE;
    uint32_t ElapsedTime = 0;
    float DeltaTime = 0.0f;
    playerActor *Player = NONE;
    UNUSED CollisionManager2D *CollisionManager = NONE;
    Camera *MainCamera = NONE;
    SDL_Window *AppWindow = NONE;
    SDL_Renderer *GfxRenderer = NONE;
    SDL_Texture *ViewPortTexture = NONE;
    UNUSED ImageLayer *Background0 = NONE;
    UNUSED ImageLayer *Background1 = NONE;
    UNUSED ImageLayer *Background2 = NONE;
    UNUSED ImageLayer *Background3 = NONE;

    LoadImageLayer(&Background0, 0, 3, WINDOW_WIDTH, WINDOW_HEIGHT, 1, TRUE, FALSE, NONE);
    LoadImageLayer(&Background1, 1, 3, WINDOW_WIDTH, WINDOW_HEIGHT, 1, TRUE, FALSE, NONE);
    LoadImageLayer(&Background2, 2, 2, WINDOW_WIDTH, WINDOW_HEIGHT, 1, TRUE, FALSE, NONE);
    LoadImageLayer(&Background3, 3, 3, WINDOW_WIDTH, WINDOW_HEIGHT, 1, TRUE, FALSE, NONE);
    SDLLoader(&GfxRenderer, &AppWindow);
    initPlayerActor(&Player, "John Doe", GfxRenderer);
    initCamera2D(&MainCamera, WINDOW_WIDTH, WINDOW_HEIGHT, GfxRenderer, NULL);
    setCameraPosition(&MainCamera, 0, 0);
    ViewPortTexture = getCameraTexture(MainCamera);
    //CollisionManager = getCollisionManager();


    while (isRunning) {
        //TODO Separate the scene into beginning (render clear, setup)->execution (update, draw, etc.) -> destroy
        DeltaTime = getDeltaTime(&ElapsedTime);
        clearRenderer(&GfxRenderer);
        //Move all business logic inside own src file

        for (int32_t textureIdx = 0; textureIdx < 3; textureIdx++) {
            DrawObjects(MainCamera, &GfxRenderer, &ViewPortTexture, NONE,
                        getTexturesContainer(Background0), textureIdx);
        }
        for (int32_t textureIdx = 0; textureIdx < 3; textureIdx++) {
            DrawObjects(MainCamera, &GfxRenderer, &ViewPortTexture, NONE,
                        getTexturesContainer(Background1), textureIdx);
        }
        for (int32_t textureIdx = 0; textureIdx < 2; textureIdx++) {
            DrawObjects(MainCamera, &GfxRenderer, &ViewPortTexture, NONE,
                        getTexturesContainer(Background2), textureIdx);
        }
        for (int32_t textureIdx = 0; textureIdx < 3; textureIdx++) {
            DrawObjects(MainCamera, &GfxRenderer, &ViewPortTexture, NONE,
                        getTexturesContainer(Background3), textureIdx);
        }
        characterEventHandler(&isRunning, getBaseChar(Player), NONE);
        updateCharacterActor(getBaseChar(Player), &DeltaTime, &GfxRenderer,
                            getObjectTexture(getBaseObj(getBaseChar(Player))));

        //CollisionManager->getIntersectionRect(getBaseObj(getBaseChar(Player)), getBaseObj(getBaseChar(Player)));
        //enemyEventHandler();

        presentRenderer(GfxRenderer);
        //Need a separate destroy method for the backgrounds to clear the texture. Currently, huge leak

        // Connected render to vsync and using delta time, so should not have much of an effect
        SDL_Delay(1000 / 60);
    }
    //FIXME Refactor with single ptr
    //destroyTexture(getObjectTexture(getBaseObj(getBaseChar(Player))));
    //destroyTexture(getCameraTexture(MainCamera));
    deinitPlayerActor(&Player);
    deinitCamera2D(&MainCamera);
    deinitCollisionManager();
    SDLUnloader(GfxRenderer, AppWindow, NULL);

    return SUCCESS;
}