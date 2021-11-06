//
// Created by Iordan Tonchev on 21.10.21.
//

#include "GameObject/GameObject2D.h"
#include "Physics/RigidBody2D.h"

//TODO Move >Transform into RigidBody?
struct gameObject{
    RigidBody2D *body2D;
    int32_t  Width;
    int32_t  Height;
    STRING spriteSheetID;
    BOOL isHFlipped;
    BOOL isVFlipped;
    BOOL isPassable;
    //TODO Add function pointers to use and above isFlags in an union
};




void drawObject();

void updateObject();


//TODO Add parameters, once it is clear how the objects
// will be initialised
void initObject(GameObject2D *self, STRING texturePath) {
    initRigidBody2D(self->body2D);
    self->Height = 0;
    self->Width = 0;
    self->isHFlipped = FALSE;
    self->isVFlipped = FALSE;
    self->spriteSheetID = texturePath;
}

void drawObject() {

}

void updateObject() {

}