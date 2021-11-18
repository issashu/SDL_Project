//
// Created by Iordan Tonchev on 16.11.21.
//

#include "Core/GameScenes/MainLevel.h"
#include "Actors/PlayerCharacter.h"
#include "Core/Camera2D.h"
#include "Core/sdl_default_app_settings.h"
#include "Core/GameEngineCore.h"
#include "Graphics/GraphicsRenderer2D.h"
#include "Managers/CharactersEventManager.h"
#include "Managers/CollisionManager.h"
#include "Utils/include/Defines.h"
#include "Timers/Timers.h"
#include "Graphics/DrawParalaxBackgrounds.h"
#include "Managers/TextureManager.h"
#include "Managers/GameObjectManager.h"
#include "Managers/GameStateManager.h"

//TODO UNIFY engine includes in a single header to pass around for convenience, when needed
void collisionWithFloor(Character *Character);

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
    CharacterEventHandler *CharacterEventManager = getCharacterEventHandler();

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

    //Characters
    UNUSED Character *Enemy = NONE;

    //INITIALISATION
    SDLLoader(&GfxRenderer, &AppWindow);

    //TODO Decide what to do with the ticket numbers returned by the pool. Right now just pulling out in a sequence
    //Objects Pool Load
    BasePlatform2D *PlatformObject = NONE;
    for (int32_t i = 0; i < MAX_PLATFORMS; i++) {
        ObjectManager->StashObjectToPool(BASIC_PLATFORM, GfxRenderer);
    }

    LoadImageLayer(&Background0, 0, 3, WINDOW_WIDTH, WINDOW_HEIGHT, 1, TRUE, FALSE, NONE);
    LoadImageLayer(&Background1, 1, 3, WINDOW_WIDTH, WINDOW_HEIGHT, 1, TRUE, FALSE, NONE);
    LoadImageLayer(&Background2, 2, 2, WINDOW_WIDTH, WINDOW_HEIGHT, 1, TRUE, FALSE, NONE);
    LoadImageLayer(&Background3, 3, 3, WINDOW_WIDTH, WINDOW_HEIGHT, 1, TRUE, FALSE, NONE);

    //Player Character Loader
    PlatformObject = (BasePlatform2D *) ObjectManager->PulloutObject(1, BASIC_PLATFORM);
    int32_t SpawnX = getObjectRect(getBaseObject(PlatformObject))->x;
    int32_t SpawnY = getObjectRect(getBaseObject(PlatformObject))->y;
    initPlayerActor(&Player, "John Doe", GfxRenderer, SpawnX + 10, SpawnY - SPRITE_HEIGHT);
    initCamera2D(&MainCamera, WINDOW_WIDTH, WINDOW_HEIGHT, GfxRenderer, NULL, 0, 0);
    setCameraPosition(&MainCamera, 0, 0);
    ViewPortTexture = getCameraTexture(MainCamera);

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
        for (int32_t ObjectKey = 1; ObjectKey < MAX_PLATFORMS; ObjectKey++) {
            PlatformObject = (BasePlatform2D *) ObjectManager->PulloutObject(ObjectKey, BASIC_PLATFORM);
            DrawSingleObject(getBaseObject(PlatformObject), &GfxRenderer,
                             getObjectTexture(getBaseObject(PlatformObject)), NONE);
        }

        //PLAYER UPDATE:
        CharacterEventManager->handleCharacterEvent(&isRunning, getBaseChar(Player), NONE);
        collisionWithFloor(getBaseChar(Player));
        CharacterEventManager->updateCharacter(getBaseChar(Player), &DeltaTime, &GfxRenderer,
                                               getObjectTexture(getBaseObj(getBaseChar(Player))));


        //COLLISIONS AND PHYSICS UPDATE:
        GameObject2D *FirstObj = getBaseObj(getBaseChar(Player));
        int32_t Overlap = 0;
        //TODO Set to multiple platform, once this is fixed
        for (int32_t i = 0; i < 1; i++) {
            GameObject2D *SecondObj = getBaseObject(PlatformObject);
            CollisionSide = CollisionManager->getIntersactionSide(FirstObj, SecondObj, &Overlap);
            switch (CollisionSide) {
                case NO_COLLISION:
                    break;
                case SIDE_UP:
                    updateBody2DTransform(&FirstObj, getObjectRect(FirstObj)->x,
                                          getObjectRect(FirstObj)->y - Overlap);
                    setAirborne(&FirstObj, FALSE);
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

        // Connected render to vsync and using delta time, so should not have much of an effect,
        // but delay to sync frames just in case
        SDL_Delay(1000 / 60);
    }
    //DEINITIALISATION

    UnloadImageLayer(&Background0);
    UnloadImageLayer(&Background1);
    UnloadImageLayer(&Background2);
    UnloadImageLayer(&Background3);

    deinitLayeredImage(&Background0);
    deinitLayeredImage(&Background1);
    deinitLayeredImage(&Background2);
    deinitLayeredImage(&Background3);

    //Remember that vector free has been modified to first remove all objects. Do not double free them!!
    deinitPlayerActor(&Player);
    deinitCamera2D(&MainCamera);
    deinitCollisionManager();
    deleteObjectManager();
    deleteObjectPool();
    deleteCharacterHandler();
    SDLUnloader(GfxRenderer, AppWindow, NULL);

    return EXIT_SUCCESS;
}

void collisionWithFloor(Character *Character) {
    int32_t CharY = getObjectRect(getBaseObj(Character))->y;
    int32_t CharHeight = getObjectRect(getBaseObj(Character))->h;
    int32_t FloorHeight = WINDOW_HEIGHT;
    if ((CharY + CharHeight) >= FloorHeight) {
        setState(Character, DEAD);
    }
}