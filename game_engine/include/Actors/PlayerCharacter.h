//
// Created by Iordan Tonchev on 4.11.21.
//

#ifndef SDL_GAME_PLAYERCHARACTER_H
#define SDL_GAME_PLAYERCHARACTER_H

#include "Actors/BaseCharacter.h"
#include "utils/defines.h"

typedef struct PlayerCharacter{
    Character *baseCharacter;
    int32_t AnimationSpeed;
    STRING spriteSheetPath;
    STRING playerName;
}playerActor;

void initPlayer(playerActor *self, int32_t AnimationSpeed, STRING Name);

#endif //SDL_GAME_PLAYERCHARACTER_H
