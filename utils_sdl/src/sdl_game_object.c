//
// Created by Iordan Tonchev on 21.10.21.
//

#include "GameObject/sdl_game_object.h"
#include "Graphics/sdl_transform2D.h"
#include "Physics/sdl_rigidBody2D.h"

struct gameObject{
    Transform2D *transform;
    RigidBody2D *body2D;
    int32_t  Width;
    int32_t  Height;
    STRING textureID;
    BOOL isHFlipped;
    BOOL isVFlipped;
    BOOL isPassable;
    //TODO Add function pointers to use and above isFlags in an union

};


void drawObject();

void updateObject();

void removeObject();

//TODO Add parameters, once it is clear how the objects
// will be initialised
void initObject(GameObject2D *self, STRING texturePath) {
    self->transform->X = 0;
    self->transform->Y = 0;
    initRigidBody2D(self->body2D);
    self->Height = 0;
    self->Width = 0;
    self->isHFlipped = FALSE;
    self->isVFlipped = FALSE;
    self->textureID = texturePath;
}

void drawObject() {

}

void updateObject() {

}

void removeObject() {

}