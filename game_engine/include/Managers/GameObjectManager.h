//
// Created by Iordan Tonchev on 23.10.21.
//

#ifndef SDL_GAME_GAMEOBJECTMANAGER_H
#define SDL_GAME_GAMEOBJECTMANAGER_H
#include <stdint.h>
#include "GameObject/GameObject2D.h"
#include "GameObject/ObjectPool.h"
#include "GameObject/Platforms/BasePlatform2D.h"

typedef struct ObjectManager {
    size_t(*StashObjectToPool)(uint8_t, SDL_Renderer*, uint32_t);
    void*(*PulloutObject)(size_t, uint8_t);
    void(*DeleteObject)(uint8_t);
    void(*ResetObject)(void*, uint8_t, STRING, STRING, int32_t, int32_t, int32_t, SDL_Renderer*);
} GameObjectManager;

GameObjectManager* getObjectManager ();
void deleteObjectManager ();


#endif //SDL_GAME_GAMEOBJECTMANAGER_H
