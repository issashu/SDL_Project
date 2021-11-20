//
// Created by Iordan Tonchev on 16.11.21.
//

#include "Actors/EnemyCharacter.h"
#include "Actors/PlayerCharacter.h"
#include "Core/GameScenes/MainLevel.h"
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
void collisionWithFloor(Character *Character, uint8_t *isRunning);

void collisionWithObjects(CollisionManager2D *CollisionManager, Character *BaseCharacter, GameObject2D *object);

BOOL mainGame() {
    //LOAD GAME LOGIC

    /*
     * Carefully consider where you put srand(). If put in a fast loop, it produces pretty much same number always.
     * Caused platform to bug and draw all at the same spot...
     * */
    //Game timers struct
    BOOL isRunning = TRUE;
    uint32_t ElapsedTime = 0;
    float DeltaTime = 0.0f;
    srand(time(NULL));

    //Player struct
    playerActor *Player = NONE;

    //Managers struct
    CollisionManager2D *CollisionManager = getCollisionManager();
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
    LoadImageLayer(&Background0, 0, 3, WINDOW_WIDTH, WINDOW_HEIGHT, 1, TRUE, FALSE, NONE);
    LoadImageLayer(&Background1, 1, 3, WINDOW_WIDTH, WINDOW_HEIGHT, 1, TRUE, FALSE, NONE);
    LoadImageLayer(&Background2, 2, 2, WINDOW_WIDTH, WINDOW_HEIGHT, 1, TRUE, FALSE, NONE);
    LoadImageLayer(&Background3, 3, 4, WINDOW_WIDTH, WINDOW_HEIGHT, 1, TRUE, FALSE, NONE);

    //Characters struct
    NPCActor *Enemies[MAX_ENEMIES];

    //INITIALISATION
    SDLLoader(&GfxRenderer, &AppWindow);

    //TODO Decide what to do with the ticket numbers returned by the pool. Right now just pulling out in a sequence
    //Objects Pool Load
    BasePlatform2D *PlatformObject = NONE;
    for (uint32_t PlatformID = 1; PlatformID <= MAX_PLATFORMS; PlatformID++) {
        ObjectManager->StashObjectToPool(BASIC_PLATFORM, GfxRenderer, PlatformID);
    }

    //Player Character Loader
    PlatformObject = (BasePlatform2D *) ObjectManager->PulloutObject(1, BASIC_PLATFORM);
    int32_t SpawnX = getObjectRect(getBaseObject(PlatformObject))->x;
    int32_t SpawnY = getObjectRect(getBaseObject(PlatformObject))->y;
    initPlayerActor(&Player, "John Doe", GfxRenderer, SpawnX + 10, SpawnY - SPRITE_HEIGHT);
    PlatformObject = NONE;

    //Non-Playable Character Loader
    for (int32_t index = 0; index < MAX_ENEMIES; index++) {
        int32_t RandSpawnLoc = rand() % MAX_PLATFORMS + 1;
        PlatformObject = (BasePlatform2D *) ObjectManager->PulloutObject(RandSpawnLoc, BASIC_PLATFORM);
        int32_t NPCX = getObjectRect(getBaseObject(PlatformObject))->x;
        int32_t NPCY = getObjectRect(getBaseObject(PlatformObject))->y;
        // void initNPCActor(NPCActor **self, char *Name, SDL_Renderer *GfxRenderer, float SpawnX, float SpawnY, uint32_t Type,
        //                  uint32_t FoVRange);
        initNPCActor(&Enemies[index], "John Doe NPC", GfxRenderer, NPCX + 10, NPCY - SPRITE_HEIGHT,
                     rand() % ALL_NPC_TYPES + 1, 150);
        PlatformObject = NONE;
    }

    //MainCamera init
    initCamera2D(&MainCamera, WINDOW_WIDTH, WINDOW_HEIGHT, GfxRenderer, NULL, 0, 0);
    setCameraPosition(&MainCamera, 0, 0);
    ViewPortTexture = getCameraTexture(MainCamera);

    //MAIN GAME LOOP
    while (isRunning) {
        //TODO Separate the scene into beginning (render clear, setup)->execution (update, draw, etc.) -> destroy
        DeltaTime = getDeltaTime(&ElapsedTime);
        clearRenderer(&GfxRenderer);

        //BACKGROUND DRAW PHASE:
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
        for (int32_t textureIdx = 0; textureIdx < 4; textureIdx++) {
            DrawObjects(MainCamera, &GfxRenderer, &ViewPortTexture, NONE,
                        getTexturesContainer(Background3), textureIdx);
        }

        //OBJECTS DRAW PHASE:
        for (int32_t ObjectKey = 1; ObjectKey <= MAX_PLATFORMS; ObjectKey++) {
            PlatformObject = (BasePlatform2D *) ObjectManager->PulloutObject(ObjectKey, BASIC_PLATFORM);
            DrawSingleObject(getBaseObject(PlatformObject), &GfxRenderer,
                             getObjectTexture(getBaseObject(PlatformObject)), NONE);
            PlatformObject = NONE;
        }

        //PLAYER EVENTS UPDATE:
        CharacterEventManager->handleCharacterEvent(&isRunning, getBaseChar(Player), NONE);
        collisionWithFloor(getBaseChar(Player), &isRunning);
        CharacterEventManager->updateCharacter(getBaseChar(Player), &DeltaTime, &GfxRenderer,
                                               getObjectTexture(getBaseObj(getBaseChar(Player))), &isRunning);


        //ENEMY EVENTS UPDATE
        for (int32_t EnemyIndex = 0; EnemyIndex < MAX_ENEMIES; EnemyIndex++) {
            DrawCharacter(IDLE_STATE, &DeltaTime, getBaseCharNPC(Enemies[EnemyIndex]), &GfxRenderer,
                          getObjectTexture(getBaseObj(getBaseCharNPC(Enemies[EnemyIndex]))));
        }

        //COLLISIONS AND PHYSICS UPDATE - PLAYER:
        for (int32_t ObjectKey = 1; ObjectKey <= MAX_PLATFORMS; ObjectKey++) {
            PlatformObject = (BasePlatform2D *) ObjectManager->PulloutObject(ObjectKey, BASIC_PLATFORM);
            collisionWithObjects(CollisionManager, getBaseChar(Player),
                                 getBaseObject(PlatformObject));

        }
        PlatformObject = NONE;

        //COLLISIONS AND PHYSICS UPDATE - ENEMIES:
        for (int32_t ObjectKey = 1; ObjectKey <= MAX_PLATFORMS; ObjectKey++) {
            for (int32_t EnemyIndex = 0; EnemyIndex < MAX_ENEMIES; EnemyIndex++) {
                PlatformObject = (BasePlatform2D *) ObjectManager->PulloutObject(ObjectKey, BASIC_PLATFORM);
                collisionWithObjects(CollisionManager, getBaseCharNPC(Enemies[EnemyIndex]),
                                     getBaseObject(PlatformObject));
            }
        }
        PlatformObject = NONE;


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

void collisionWithFloor(Character *Character, UNUSED uint8_t *isRunning) {
    int32_t CharY = getObjectRect(getBaseObj(Character))->y;
    int32_t CharHeight = getObjectRect(getBaseObj(Character))->h;
    int32_t FloorHeight = WINDOW_HEIGHT;
    if ((CharY + CharHeight) >= FloorHeight - 60) {
        setState(Character, DEAD);
        //*isRunning = FALSE;
    }
}

void collisionWithObjects(CollisionManager2D *CollisionManager, Character *BaseCharacter, GameObject2D *object) {
    GameObject2D *Character = getBaseObj(BaseCharacter);
    uint8_t CollisionSide = 0;
    int32_t Overlap = 0;
    //TODO Set to multiple platform, once this is fixed
    for (int32_t i = 0; i < 1; i++) {
        CollisionSide = CollisionManager->getIntersactionSide(Character, object, &Overlap);
        switch (CollisionSide) {
            case NO_COLLISION:
                break;
            case SIDE_UP:
                updateBody2DTransform(&Character, getObjectRect(Character)->x,
                                      getObjectRect(Character)->y - Overlap);
                setAirborne(&Character, FALSE);
                break;
            case SIDE_LEFT:
                break;
            case SIDE_DOWN:
                /*updateBody2DTransform(&Character,getObjectRect(Character)->x,
                                      getObjectRect(SecondObj)->y+Overlap);*/
                break;
            case SIDE_RIGHT:
                break;
            default:
                break;
        }
    }
}