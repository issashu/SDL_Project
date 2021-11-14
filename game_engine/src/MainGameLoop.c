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
#include "Managers/GameObjectManager.h"
#include "Managers/GameStateManager.h"

BOOL mainGame() {
    BOOL isRunning = TRUE;
    uint32_t ElapsedTime = 0;
    float DeltaTime = 0.0f;
    playerActor *Player = NONE;
    CollisionManager2D *CollisionManager = NONE;
    UNUSED GameObjectManager *ObjectManager = NONE;
    Camera *MainCamera = NONE;
    SDL_Window *AppWindow = NONE;
    SDL_Renderer *GfxRenderer = NONE;
    SDL_Texture *ViewPortTexture = NONE;
    uint8_t CollisionSide;
    ImageLayer *Background0 = NONE;
    ImageLayer *Background1 = NONE;
    ImageLayer *Background2 = NONE;
    ImageLayer *Background3 = NONE;

    BasePlatform2D *Platform1 = NONE;
    BasePlatform2D *Platform2 = NONE;
    BasePlatform2D *Platform3 = NONE;
    BasePlatform2D *Platform4 = NONE;
    BasePlatform2D *Platform5 = NONE;
    BasePlatform2D *Platform6 = NONE;

    //INITIALISATION
    SDLLoader(&GfxRenderer, &AppWindow);
    initBasePlatform(&Platform1, ASSETS_PATH "images/Platform.png", "Platform1", 150, 20, 100, GfxRenderer, 10, 500);
    initBasePlatform(&Platform2, ASSETS_PATH "images/Platform.png", "Platform2", 150, 20, 100, GfxRenderer, 700, 500);
    initBasePlatform(&Platform3, ASSETS_PATH "images/Platform.png", "Platform3", 150, 20, 100, GfxRenderer, 450, 550);
    initBasePlatform(&Platform4, ASSETS_PATH "images/Platform.png", "Platform4", 150, 20, 100, GfxRenderer, 100, 650);
    initBasePlatform(&Platform5, ASSETS_PATH "images/Platform.png", "Platform5", 150, 20, 100, GfxRenderer, 675, 770);
    initBasePlatform(&Platform6, ASSETS_PATH "images/Platform.png", "Platform6", 150, 20, 100, GfxRenderer, 200, 600);

    BasePlatform2D* PlatformsArray[6];
    PlatformsArray[0]=Platform1;
    PlatformsArray[1]=Platform2;
    PlatformsArray[2]=Platform3;
    PlatformsArray[3]=Platform4;
    PlatformsArray[4]=Platform5;
    PlatformsArray[5]=Platform6;

    LoadImageLayer(&Background0, 0, 3, WINDOW_WIDTH, WINDOW_HEIGHT, 1, TRUE, FALSE, NONE);
    LoadImageLayer(&Background1, 1, 3, WINDOW_WIDTH, WINDOW_HEIGHT, 1, TRUE, FALSE, NONE);
    LoadImageLayer(&Background2, 2, 2, WINDOW_WIDTH, WINDOW_HEIGHT, 1, TRUE, FALSE, NONE);
    LoadImageLayer(&Background3, 3, 3, WINDOW_WIDTH, WINDOW_HEIGHT, 1, TRUE, FALSE, NONE);

    initPlayerActor(&Player, "John Doe", GfxRenderer, 10, 400);
    initCamera2D(&MainCamera, WINDOW_WIDTH, WINDOW_HEIGHT, GfxRenderer, NULL, 0, 0);
    setCameraPosition(&MainCamera, 0, 0);
    ViewPortTexture = getCameraTexture(MainCamera);
    CollisionManager = getCollisionManager();

    while (isRunning) {
        //TODO Separate the scene into beginning (render clear, setup)->execution (update, draw, etc.) -> destroy
        DeltaTime = getDeltaTime(&ElapsedTime);
        clearRenderer(&GfxRenderer);

        //TODO Move all business logic inside own src file

        //BACKGROUND UPDATE:
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

        //OBJECTS UPDATE:
        for (int32_t i =0; i<6; i++) {
            GameObject2D *tmpObj = getBaseObject(PlatformsArray[i]);
            drawStatic(&GfxRenderer, getObjectTexture(tmpObj), NONE, getObjectRect(tmpObj));
        }

        //PLAYER UPDATE:
        characterEventHandler(&isRunning, getBaseChar(Player), NONE);
        updateCharacterActor(getBaseChar(Player), &DeltaTime, &GfxRenderer,
                            getObjectTexture(getBaseObj(getBaseChar(Player))));

        //COLLISIONS AND PHYSICS UPDATE:
        GameObject2D *FirstObj = getBaseObj(getBaseChar(Player));
        int32_t Overlap = 0;
        for (int32_t i= 0; i<6; i++) {
            GameObject2D *SecondObj = getBaseObject(PlatformsArray[i]);
            CollisionSide = CollisionManager->getIntersactionSide(FirstObj, SecondObj, &Overlap);
            switch (CollisionSide) {
                case NO_COLLISION:
                    break;
                case SIDE_UP:
                    updateBody2DTransform(&FirstObj,getObjectRect(FirstObj)->x,
                                          getObjectRect(FirstObj)->y-Overlap);
                    break;
                case SIDE_LEFT:
                    break;
                case SIDE_DOWN:
                    updateBody2DTransform(&FirstObj,getObjectRect(FirstObj)->x,
                                          getObjectRect(SecondObj)->y+Overlap);
                    break;
                case SIDE_RIGHT:
                    break;
                default:
                    break;
            }
        }
        //ENEMY UPDATES

        //PRESENT RENDERER AND MISC
        presentRenderer(GfxRenderer);

        // Connected render to vsync and using delta time, so should not have much of an effect
        SDL_Delay(1000 / 60);
    }
    //FIXME Refactor with single ptr
    deinitBasePlatform(&Platform1);
    deinitBasePlatform(&Platform2);
    deinitBasePlatform(&Platform3);
    deinitBasePlatform(&Platform4);
    deinitBasePlatform(&Platform5);
    deinitBasePlatform(&Platform6);

    deinitLayeredImage(&Background0);
    deinitLayeredImage(&Background1);
    deinitLayeredImage(&Background2);
    deinitLayeredImage(&Background3);

    deinitPlayerActor(&Player);
    deinitCamera2D(&MainCamera);
    deinitCollisionManager();
    SDLUnloader(GfxRenderer, AppWindow, NULL);

    return SUCCESS;
}