//
// Created by Iordan Tonchev on 20.11.21.
//

#include <stdlib.h>
#include "Actors/EnemyCharacter.h"

/*------------- PRIVATE: -----------------------*/
struct NPCCharacter {
    Character *baseCharacter;
    SDL_Rect FieldfOfView;
    uint32_t NPCType;
    STRING spriteSheetPath;
    STRING NPCName;
};

/*------------- PUBLIC: -----------------------*/

void initNPCActor(NPCActor **self, char *Name, SDL_Renderer *GfxRenderer, float SpawnX, float SpawnY, uint32_t Type,
                  uint32_t FoVRange) {
    *self = (NPCActor *) malloc(sizeof(struct NPCCharacter));
    //TODO Replace with a proper pointer array to textures and maybe implement flyweight
    switch (Type) {
        case CASTER:
            (*self)->spriteSheetPath = ASSETS_PATH "images/Enemies/enemy_sheet_red.png";
            break;
        case FIGHTER:
            (*self)->spriteSheetPath = ASSETS_PATH "images/Enemies/enemy_sheet_blue.png";

            break;
        case CLERIC:
            (*self)->spriteSheetPath = ASSETS_PATH "images/Enemies/enemy_sheet_green.png";
            break;
        case ROGUE:
            (*self)->spriteSheetPath = ASSETS_PATH "images/Enemies/enemy_sheet_yellow.png";
            break;
        case GENERIC:
        default:
            (*self)->spriteSheetPath = ASSETS_PATH "images/Enemies/enemy_sheet_black.png";
            break;
    }
    (*self)->FieldfOfView.w = FoVRange;
    (*self)->FieldfOfView.h = 80;
    (*self)->NPCType = Type;
    (*self)->NPCName = Name;
    initCharacter(&(*self)->baseCharacter, (*self)->spriteSheetPath, GfxRenderer, SpawnX, SpawnY);
}

void deinitNPCActor(NPCActor **self) {
    if (*self != NONE) {
        deinitCharacter(&(*self)->baseCharacter);
        free(*self);
        *self = NONE;
    }
}

Character *getBaseCharNPC(struct NPCCharacter *self) {
    return self->baseCharacter;
}

STRING getNPCName(NPCActor *self) {
    return self->NPCName;
}

STRING getNPCSpriteSheetPath(struct NPCCharacter *self) {
    return self->spriteSheetPath;
}

void setNPCName(NPCActor *self, STRING Name) {
    self->NPCName = Name;
}

int32_t getNPCState(NPCActor *self) {
    return getState(self->baseCharacter);
}

void setNPCState(NPCActor *self, int32_t state) {
    setState(self->baseCharacter, state);
}

