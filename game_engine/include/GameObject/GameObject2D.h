//
// Created by Iordan Tonchev on 21.10.21.
//

#ifndef SDL_GAME_GAMEOBJECT2D_H
#define SDL_GAME_GAMEOBJECT2D_H

#include <stdint.h>
#include "utils/defines.h"

typedef struct gameObject GameObject2D;

void initObject(GameObject2D *self, STRING texturePath);

#endif //SDL_GAME_GAMEOBJECT2D_H
