//
// Created by Iordan Tonchev on 6.11.21.
//

#ifndef SDL_GAME_COLLIDER2D_H
#define SDL_GAME_COLLIDER2D_H

#include "utils/defines.h"

typedef struct Collider2D Collider2D;

void initCollider2D (Collider2D *Collider, int32_t X, int32_t Y, int32_t W, int32_t H, int32_t Scale, STRING Tag);
void deinitCollider2D (Collider2D *Collider);
BOOL getColliderStatus (Collider2D *Collider);
void setColliderStatus(Collider2D *Collider, BOOL NewStatus);
void ScaleCollider2D(Collider2D *Collider, int32_t Scale);

#endif //SDL_GAME_COLLIDER2D_H