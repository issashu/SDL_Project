//
// Created by Iordan Tonchev on 20.11.21.
//

#ifndef SDL_GAME_ENEMYCHARACTER_H
#define SDL_GAME_ENEMYCHARACTER_H

#include "Actors/BaseCharacter.h"
#include "Utils/include/Defines.h"

enum EnemyTypes {
    GENERIC = 0,
    CASTER,
    FIGHTER,
    CLERIC,
    ROGUE,
    ALL_NPC_TYPES
};

#define MAX_ENEMIES 3

typedef struct NPCCharacter NPCActor;

void initNPCActor(NPCActor **self, char *Name, SDL_Renderer *GfxRenderer, float SpawnX, float SpawnY, uint32_t Type,
                  uint32_t FoVRange);
void deinitNPCActor(NPCActor **self);
Character *getBaseCharNPC(struct NPCCharacter *self);
STRING getNPCName(NPCActor *self);
STRING getNPCSpriteSheetPath(struct NPCCharacter *self);
void setNPCName(NPCActor *self, STRING Name);
int32_t getNPCState(NPCActor *self);
void setNPCState(NPCActor *self, int32_t state);


#endif //SDL_GAME_ENEMYCHARACTER_H
