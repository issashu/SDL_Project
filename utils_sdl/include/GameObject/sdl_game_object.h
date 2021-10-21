//
// Created by Iordan Tonchev on 21.10.21.
//

#ifndef SDL_GAME_SDL_GAME_OBJECT_H
#define SDL_GAME_SDL_GAME_OBJECT_H

#include <stdint.h>
#include "defines.h"

typedef struct gameObject{
    struct Transform2D *transform;
    int32_t  Width;
    int32_t  Height;
    STRING textureID;
    BOOL isHFlipped;
    BOOL isVFlipped;
    //TODO Add function pointers to use

} GameObject;

#endif //SDL_GAME_SDL_GAME_OBJECT_H
