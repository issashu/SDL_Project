//
// Created by Iordan Tonchev on 16.11.21.
//

#include "Core/GameScenes/MainLevel.h"
#include "Actors/PlayerCharacter.h"
#include "Core/Camera2D.h"
#include "Core/sdl_default_app_settings.h"
#include "Core/GameEngineCore.h"
#include "Graphics/GraphicsRenderer2D.h"
#include "Managers/EventManager.h"
#include "Managers/CollisionManager.h"
#include "Utils/include/Defines.h"
#include "Timers/Timers.h"
#include "Graphics/DrawParalaxBackgrounds.h"
#include "Managers/TextureManager.h"
#include "Managers/GameObjectManager.h"
#include "Managers/GameStateManager.h"


//TODO UNIFY engine includes in a single header to pass around for convenience, when needed
BOOL mainGame() {
    //LOAD GAME LOGIC

    //Game timers struct
    BOOL isRunning = TRUE;
    uint32_t ElapsedTime = 0;
    float DeltaTime = 0.0f;

    //Player struct
    playerActor *Player = NONE;

    //Managers struct
    CollisionManager2D *CollisionManager = getCollisionManager();
    uint8_t CollisionSide;
    GameObjectManager *ObjectManager = getObjectManager();
    EventHandler *CharacterEventManager = getCharacterEventHandler();

    //Graphics struct
    Camera *MainCamera = NONE;
    SDL_Window *AppWindow = NONE;
    SDL_Renderer *GfxRenderer = NONE;
    SDL_Texture *ViewPortTexture = NONE;

    //Backgrounds struct (maybe make a fast manager for that)
    ImageLayer *Background0 = NONE;
    ImageLayer *Background1 = NONE;
    ImageLayer *Background2 = NONE;
    ImageLayer *Background3 = NONE;

    //Objects Pool
    BasePlatform2D *PlatformTest = NONE;

    //INITIALISATION
    SDLLoader(&GfxRenderer, &AppWindow);

    //TODO Decide what to do with the ticket numbers
    size_t ObjectKey = ObjectManager->LoadObjectToPool(BASIC_PLATFORM);
    printf("%zu", ObjectKey);
    PlatformTest = ObjectManager->SpawnObject(ObjectKey, BASIC_PLATFORM);

    initBasePlatform(&PlatformTest, ASSETS_PATH "images/Platform.png", "Platform6", 150, 20, 100, GfxRenderer, 10, 500);

    BasePlatform2D* PlatformsArray[1];
    PlatformsArray[0]=PlatformTest;

    LoadImageLayer(&Background0, 0, 3, WINDOW_WIDTH, WINDOW_HEIGHT, 1, TRUE, FALSE, NONE);
    LoadImageLayer(&Background1, 1, 3, WINDOW_WIDTH, WINDOW_HEIGHT, 1, TRUE, FALSE, NONE);
    LoadImageLayer(&Background2, 2, 2, WINDOW_WIDTH, WINDOW_HEIGHT, 1, TRUE, FALSE, NONE);
    LoadImageLayer(&Background3, 3, 3, WINDOW_WIDTH, WINDOW_HEIGHT, 1, TRUE, FALSE, NONE);

    initPlayerActor(&Player, "John Doe", GfxRenderer, 10, 400);
    initCamera2D(&MainCamera, WINDOW_WIDTH, WINDOW_HEIGHT, GfxRenderer, NULL, 0, 0);
    setCameraPosition(&MainCamera, 0, 0);
    ViewPortTexture = getCameraTexture(MainCamera);
    CollisionManager = getCollisionManager();

    //MAIN GAME LOOP
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
        for (int32_t i =0; i<1; i++) {
            GameObject2D *tmpObj = getBaseObject(PlatformsArray[i]);
            drawStatic(&GfxRenderer, getObjectTexture(tmpObj), NONE, getObjectRect(tmpObj));
        }

        //PLAYER UPDATE:
        CharacterEventManager->handleCharacterEvent(&isRunning, getBaseChar(Player), NONE);
        CharacterEventManager->updateCharacter(getBaseChar(Player), &DeltaTime, &GfxRenderer,
                                               getObjectTexture(getBaseObj(getBaseChar(Player))));


        //COLLISIONS AND PHYSICS UPDATE:
        GameObject2D *FirstObj = getBaseObj(getBaseChar(Player));
        int32_t Overlap = 0;
        for (int32_t i= 0; i<1; i++) {
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
                    /*updateBody2DTransform(&FirstObj,getObjectRect(FirstObj)->x,
                                          getObjectRect(SecondObj)->y+Overlap);*/
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
    //DEINITIALISATION
    deinitBasePlatform(&PlatformTest);

    UnloadImageLayer(&Background0);
    UnloadImageLayer(&Background1);
    UnloadImageLayer(&Background2);
    UnloadImageLayer(&Background3);

    deinitLayeredImage(&Background0);
    deinitLayeredImage(&Background1);
    deinitLayeredImage(&Background2);
    deinitLayeredImage(&Background3);

    deinitPlayerActor(&Player);
    deinitCamera2D(&MainCamera);
    deinitCollisionManager();
    deleteObjectManager();
    deleteObjectManager();
    deleteCharacterHandler();
    SDLUnloader(GfxRenderer, AppWindow, NULL);

    return EXIT_SUCCESS;
}