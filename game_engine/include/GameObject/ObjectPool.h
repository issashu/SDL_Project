//
// Created by Iordan Tonchev on 1.11.21.
//

#ifndef SDL_GAME_OBJECTPOOL_H
#define SDL_GAME_OBJECTPOOL_H
#include "GameObject/GameObject2D.h"
#include "utils/containers/Vector.h"

typedef struct ObjectPool2D {
    void (*StashObject)(struct Vector *, GameObject2D *);
    GameObject2D* (*TakeOutObject)(uint8_t);
} ObjectPool;

ObjectPool* getObjectPool ();
void deleteObjectPool ();

#endif //SDL_GAME_OBJECTPOOL_H