//
// Created by Iordan Tonchev on 22.10.21.
//

#include <MacTypes.h>
#include "Actors/sdl_character.h"

void updateCharacter();

void removeCharacter();


void initCharacter(Character *self, STRING name, STRING texturePath) {
    initObject(self->Base2D, texturePath);
    self->Name = name;
    self->Health = 100;
    self->Mana = 100;
    self->isAlive = TRUE;
    self->stateFlags = 0;
}