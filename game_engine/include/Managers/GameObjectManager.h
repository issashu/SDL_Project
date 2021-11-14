//
// Created by Iordan Tonchev on 23.10.21.
//

#ifndef SDL_GAME_GAMEOBJECTMANAGER_H
#define SDL_GAME_GAMEOBJECTMANAGER_H
#include <stdint.h>
#include "GameObject/GameObject2D.h"
#include "GameObject/ObjectPool.h"
#include "GameObject/Platforms/BasePlatform2D.h"

//TODO Apply singleton

typedef struct ObjectManager {
    size_t(*LoadObjectToPool)(void*, uint8_t);
    void(*DespawnObject)(uint8_t);
    void(*ResetObject)(void*, uint8_t, STRING, STRING, int32_t, int32_t, int32_t, SDL_Renderer*);
} GameObjectManager;

GameObjectManager* getObjectManager ();
void deleteObjectManager ();


#endif //SDL_GAME_GAMEOBJECTMANAGER_H
