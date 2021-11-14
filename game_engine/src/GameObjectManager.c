//
// Created by Iordan Tonchev on 23.10.21.
//

#include <stdint.h>
#include "Managers/GameObjectManager.h"

/*------------- PRIVATE: -----------------------*/

static GameObjectManager *self= NONE;

size_t LoadGameObjects(void *GameObject, uint8_t ObjectType);
void deSpawnObject(uint8_t Position);
void resetGameObject(void *object, uint8_t ObjectType,STRING TexturePath, STRING Tag, int32_t Width, int32_t Height,
                     int32_t Health, SDL_Renderer* GfxRenderer);


/*------------- PUBLIC: -----------------------*/
//TODO Decide about hard-coding the object number and usage of flag (if needed at all)
GameObjectManager* getObjectManager () {
    if (self == NONE) {
        self = (GameObjectManager*)malloc(sizeof(struct ObjectManager));
        self->LoadObjectToPool = &LoadGameObjects;
        self->DespawnObject = &deSpawnObject;
        self->ResetObject = &resetGameObject;
    }
    return self;
}

void deleteObjectManager () {
    if (self != NONE) {
        free(self);
        self = NONE;
    }
}

/*------------- IMPLEMENTATION: -----------------------*/

//TODO Find a less naive implementation (type agnostic). Work for now, since we only have platforms
size_t LoadGameObjects(void *GameObject, uint8_t ObjectType) {
    ObjectPool *tmpPool = getObjectPool();
    size_t PositionTicket = 0;
    PositionTicket = tmpPool->StashObject(GameObject, ObjectType);

    return PositionTicket;
}

//TODO Add the remaining types of objects. For demo only base platform
void* SpawnGameObjects(size_t Position, uint8_t Type) {
    ObjectPool *tmpPool = getObjectPool();
    void *object = NONE;
    switch (Type) {
        case BASIC_PLATFORM:
            object = (BasePlatform2D*) object;
            object = tmpPool->TakeOutObject(Position);
        case FALL_THROUGH_TRAP:
            break;
        case SPIKE_TRAP:
            break;
        case HEALING_POTION:
            break;
        case MANA_POTION:
            break;
        case BONUS_POINTS_ITEM:
            break;
        case GENERIC_GAME_OBJECT:
            break;
        default:
            break;
    }

    return object;
}


//TODO Need to tie the LibraryCards to the ObjectContainer positions, so that the cards update, when an object is deleted
// Works for now, since we have few items only and don't intend to resize
void deSpawnObject(uint8_t Position) {
    ObjectPool *tmpPool = getObjectPool();
    tmpPool->TrashObject(Position);
}

//TODO Add multiple behaviours based on type of object (once more objects are added to the game)
void updateGameObject() {

}

//TODO Try and see why the compiler complains, when passing double pointer to the init function. Meanwhile avoid using
void resetGameObject(void *object, uint8_t ObjectType,STRING TexturePath, STRING Tag, int32_t Width, int32_t Height,
                     int32_t Health, SDL_Renderer* GfxRenderer) {
    switch (ObjectType) {
        case BASIC_PLATFORM:
            object = (BasePlatform2D*) object;
            initBasePlatform(object, TexturePath, Tag, Width, Height, Health, GfxRenderer, 0, 0);
            break;
        case FALL_THROUGH_TRAP:
            break;
        case SPIKE_TRAP:
            break;
        case HEALING_POTION:
            break;
        case MANA_POTION:
            break;
        case BONUS_POINTS_ITEM:
            break;
        case GENERIC_GAME_OBJECT:
            object = (GameObject2D *) object;
            initBasePlatform(object, TexturePath, Tag, Width, Height, Health, GfxRenderer, 0, 0);
            break;
        default:
            break;
    }
}