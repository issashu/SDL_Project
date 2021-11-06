//
// Created by Iordan Tonchev on 4.11.21.
//

#ifndef SDL_GAME_PLAYER_H
#define SDL_GAME_PLAYER_H

#include "Actors/BaseCharacter.h"
#include "utils/defines.h"

typedef struct Player{
    Character baseCharacter;
    int32_t AnimationSpeed;
    STRING spriteSheetPath;
    STRING playerName;
}playerActor;

#endif //SDL_GAME_PLAYER_H
