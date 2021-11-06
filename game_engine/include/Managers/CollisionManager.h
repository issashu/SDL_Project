//
// Created by Iordan Tonchev on 6.11.21.
//

#ifndef SDL_GAME_COLLISIONMANAGER_H
#define SDL_GAME_COLLISIONMANAGER_H

#include <SDL.h>

#include "Physics/Collider2D.h"
#include "utils/defines.h"

BOOL CheckCollision2D (Collider2D *Collider, SDL_Rect *obj);

#endif //SDL_GAME_COLLISIONMANAGER_H
