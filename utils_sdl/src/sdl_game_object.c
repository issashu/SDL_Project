//
// Created by Iordan Tonchev on 21.10.21.
//

#include "GameObject/sdl_game_object.h"
#include "utils/include/utils/containers/Vector.h"
#include "Physics/sdl_transform2D.h"

void drawObject();

void updateObject();

void removeObject();

void initObject();

//TODO Add parameters, once it is clear how the objects
// will be initialised
void initObject(GameObject *self) {
    self->transform->X = 0;
    self->transform->Y = 0;
    self->Height = 0;
    self->Width = 0;
    self->isHFlipped = FALSE;
    self->isVFlipped = FALSE;
    self->textureID = "Replace with texture string";
}

void drawObject() {

}

void updateObject() {

}

void removeObject() {

}