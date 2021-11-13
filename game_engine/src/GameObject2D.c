//
// Created by Iordan Tonchev on 21.10.21.
//

#include <stdlib.h>
#include <SDL_render.h>

#include "GameObject/GameObject2D.h"
#include "Physics/RigidBody2D.h"
#include "utils/defines.h"

/*------------- PRIVATE: -----------------------*/
struct GameObject {
    RigidBody2D *body2D;
    SDL_Rect ObjectRect;
    SDL_Texture *ObjTexture;
    BOOL isHFlipped;
    BOOL isVFlipped;
    BOOL isPassable;
    BOOL isAlive;
    //TODO Add function pointers to use and set Flag in a bitfield?
};

/*------------- PUBLIC: -----------------------*/
//TODO Add parameters, once it is clear how the objects
// will be initialised and take what is needed from player class. Also rework the texture load to get it from the vector storage container
//FIXME Set the w and h universally on init via set (different objects and sizes)
void initObject(GameObject2D **self, int32_t Width, int32_t Height) {
    *self = (GameObject2D *) malloc(sizeof(struct GameObject));
    initRigidBody2D(&(*self)->body2D);
    (*self)->ObjectRect.x = (int) getTransformX((*self)->body2D);
    (*self)->ObjectRect.y = (int) getTransformY((*self)->body2D);
    (*self)->ObjectRect.w = Width;
    (*self)->ObjectRect.h = Height;
    (*self)->ObjTexture = NONE;
    (*self)->isHFlipped = FALSE;
    (*self)->isVFlipped = FALSE;
    (*self)->isPassable = TRUE;
    (*self)->isAlive = FALSE;
}

void deinitObject(GameObject2D **self) {
    if (*self != NONE) {
        deinitRigidBody2D(&(*self)->body2D);
        free(*self);
        *self = NONE;
    }
}

SDL_Rect *getObjectRect(GameObject2D *self) {
    return &self->ObjectRect;
}

SDL_Texture **getObjectTexture(GameObject2D *self) {
    return &self->ObjTexture;
}

BOOL getHorrizFlip(GameObject2D *self) {
    return self->isHFlipped;
}

BOOL getVertFlip(GameObject2D *self) {
    return self->isVFlipped;
}

BOOL getPassable(GameObject2D *self) {
    return self->isPassable;
}

BOOL getAlive(GameObject2D *self) {
    return self->isAlive;
}

void setHorrizFlip(GameObject2D *self, BOOL flag) {
    self->isHFlipped = flag;
}

void setVertFlip(GameObject2D *self, BOOL flag) {
    self->isVFlipped = flag;
}

void setPassable(GameObject2D *self, BOOL flag) {
    self->isPassable = flag;
}

void setAlive(GameObject2D *self, BOOL flag) {
    self->isAlive = flag;
}

void updateObject(GameObject2D **self, float DeltaTime, Vector2D *Force, Vector2D *Friction) {
    updatePosition(&(*self)->body2D, DeltaTime, Force, Friction);
    (*self)->ObjectRect.x = (int) getTransformX((*self)->body2D);
    (*self)->ObjectRect.y = (int) getTransformY((*self)->body2D);
}


