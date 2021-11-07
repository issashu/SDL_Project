//
// Created by Iordan Tonchev on 4.11.21.
//
#include <stdlib.h>
#include "Actors/PlayerCharacter.h"

void initPlayer(playerActor *self, int32_t AnimationSpeed, STRING Name) {
    self = (playerActor *) malloc (sizeof(struct PlayerCharacter));
    self->spriteSheetPath = ASSETS_PATH "images/character_anim.png";
    self->AnimationSpeed = AnimationSpeed;
    self->playerName = Name;
    initCharacter(self->baseCharacter, self->spriteSheetPath);
}
