//
// Created by Iordan Tonchev on 6.11.21.
//

#ifndef SDL_GAME_COLLISIONMANAGER_H
#define SDL_GAME_COLLISIONMANAGER_H

#include "GameObject/GameObject2D.h"
#include "utils/defines.h"

typedef struct CollisionManager {
    BOOL (*CheckCollision)(GameObject2D *, GameObject2D *);
    uint8_t (*getIntersactionSide)(GameObject2D *, GameObject2D *, int32_t *);
    SDL_Rect (*getIntersectionRect)(GameObject2D *, GameObject2D *);

} CollisionManager2D;

CollisionManager2D *getCollisionManager();

void deinitCollisionManager();


#endif //SDL_GAME_COLLISIONMANAGER_H
