//
// Created by Iordan Tonchev on 4.11.21.
//

#ifndef SDL_GAME_PLAYERCHARACTER_H
#define SDL_GAME_PLAYERCHARACTER_H

#include "Actors/BaseCharacter.h"
#include "Utils/include/Defines.h"

typedef struct PlayerCharacter playerActor;

void initPlayerActor(playerActor **self, char *Name, SDL_Renderer *GfxRenderer, float SpawnX, float SpawnY);
void deinitPlayerActor(playerActor **self);

Character* getBaseChar (struct PlayerCharacter *self);
STRING getPlayerName(playerActor *self);
STRING getSpriteSheetPath (playerActor *self);
void setPlayerName(playerActor *self, STRING Name);
int32_t getPlayerState (playerActor *self);
void setPlayerState(playerActor *self, int32_t state);

#endif //SDL_GAME_PLAYERCHARACTER_H
