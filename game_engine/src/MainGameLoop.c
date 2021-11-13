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
    CollisionManager2D *CollisionManager = NONE;
    Camera *MainCamera = NONE;
    SDL_Window *AppWindow = NONE;
    SDL_Renderer *GfxRenderer = NONE;
    ImageLayer *Background0 = NONE;
    ImageLayer *Background1 = NONE;
    ImageLayer *Background2 = NONE;
    ImageLayer *Background3 = NONE;

    initCamera2D(&MainCamera, WINDOW_WIDTH, WINDOW_HEIGHT);
    setCameraPosition(&MainCamera, 0, 0);
    LoadImageLayer(&Background0, 0, 3, WINDOW_WIDTH, WINDOW_HEIGHT, 1, TRUE, FALSE, NONE);
    LoadImageLayer(&Background1, 1, 3, WINDOW_WIDTH, WINDOW_HEIGHT, 1, TRUE, FALSE, NONE);
    LoadImageLayer(&Background2, 2, 2, WINDOW_WIDTH, WINDOW_HEIGHT, 1, TRUE, FALSE, NONE);
    LoadImageLayer(&Background3, 3, 3, WINDOW_WIDTH, WINDOW_HEIGHT, 1, TRUE, FALSE, NONE);

    initPlayerActor(&Player, "John Doe");
    CollisionManager = getCollisionManager();
    SDLLoader(Player, &GfxRenderer, &AppWindow);

    while (isRunning) {
        //TODO Separate the scene into beginning (render clear, setup)->execution (update, draw, etc.) -> destroy
        DeltaTime = getDeltaTime(&ElapsedTime);
        clearRenderer(&GfxRenderer);
        //Move all business logic inside own src file
        for (int32_t textureIdx = 0; textureIdx < 3; textureIdx++) {
            DrawObjects(MainCamera, &GfxRenderer, getCameraTexture(MainCamera), NONE,
                        getTexturesContainer(Background0), textureIdx);
        }
        for (int32_t textureIdx = 0; textureIdx < 3; textureIdx++) {
            DrawObjects(MainCamera, &GfxRenderer, getCameraTexture(MainCamera), NONE,
                        getTexturesContainer(Background1), textureIdx);
        }
        for (int32_t textureIdx = 0; textureIdx < 2; textureIdx++) {
            DrawObjects(MainCamera, &GfxRenderer, getCameraTexture(MainCamera), NONE,
                        getTexturesContainer(Background2), textureIdx);
        }
        for (int32_t textureIdx = 0; textureIdx < 3; textureIdx++) {
            DrawObjects(MainCamera, &GfxRenderer, getCameraTexture(MainCamera), NONE,
                        getTexturesContainer(Background3), textureIdx);
        }
        characterEventHandler(&isRunning, getBaseChar(Player), NONE);

        updateCharacterActor(getBaseChar(Player), &DeltaTime, &GfxRenderer,
                            getObjectTexture(getBaseObj(getBaseChar(Player))));

        //TODO Replace print with actual collision manager mechanic
        printf("%d", CollisionManager->CheckCollision(getBaseObj(getBaseChar(Player)),
                                                      getBaseObj(getBaseChar(Player))));

        //enemyEventHandler();

        presentRenderer(GfxRenderer);
        //Need a separate destroy method for the backgrounds to clear the texture. Currently, huge leak
        //destroyTexture(getTexturesContainer(Background0));
        destroyTexture(getObjectTexture(getBaseObj(getBaseChar(Player))));
        destroyTexture(getCameraTexture(MainCamera));

        // Connected render to vsync and using delta time, so should not have much of an effect
        SDL_Delay(1000 / 60);
    }
    deinitPlayerActor(&Player);
    deinitCamera2D(&MainCamera);
    SDLUnloader(GfxRenderer, AppWindow, NULL);

    return SUCCESS;
}