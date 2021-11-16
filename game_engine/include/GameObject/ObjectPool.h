//
// Created by Iordan Tonchev on 1.11.21.
//

#ifndef SDL_GAME_OBJECTPOOL_H
#define SDL_GAME_OBJECTPOOL_H
#include "GameObject/GameObject2D.h"
#include "Utils/include/containers/Vector.h"

/**
 * StashObject is used to insert an item in the object pool.
 *     Please supply an object and it's type based on the ObjectTypes enum
 */
typedef struct ObjectPool2D {
    size_t (*StashObject)(void *, uint8_t);
    void * (*TakeOutObject)(uint8_t);
    void (*TrashObject)(uint8_t);
} ObjectPool;

ObjectPool* getObjectPool ();
void deleteObjectPool ();

#endif //SDL_GAME_OBJECTPOOL_H