//
// Created by Iordan Tonchev on 21.10.21.
//

#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "GameObject/GameObject2D.h"
#include "Physics/RigidBody2D.h"
#include "Utils/include/Defines.h"
#include "Managers/TextureManager.h"

/*------------- PRIVATE: -----------------------*/
struct GameObject {
    RigidBody2D *body2D;
    SDL_Texture *ObjTexture;
    SDL_Rect ObjectRect;
    float ObjectRadius;
    uint8_t PositionInObjectPool;
    //TODO Add Flags Bitfield/Union to reduce size
    BOOL isHFlipped;
    BOOL isVFlipped;
    BOOL isPassable;
    BOOL isAlive;

};

/*------------- PUBLIC: -----------------------*/
//TODO Add parameters, once it is clear how the objects
// will be initialised and take what is needed from player class. Also rework the texture load to get it from the vector storage container
//FIXME Set the w and h universally on init via set (different objects and sizes)
void initObject(GameObject2D **self, uint8_t PositionInPool, int32_t Width, int32_t Height, SDL_Renderer *GfxRenderer,
                char *TexturePath, float SpawnX, float SpawnY) {
    *self = (GameObject2D *) malloc(sizeof(struct GameObject));
    initRigidBody2D(&(*self)->body2D, SpawnX, SpawnY);
    (*self)->ObjectRect.x = (int) getTransformX((*self)->body2D);
    (*self)->ObjectRect.y = (int) getTransformY((*self)->body2D);
    (*self)->ObjectRect.w = Width;
    (*self)->ObjectRect.h = Height;
    (*self)->ObjectRadius = Width * HALF;
    (*self)->PositionInObjectPool = PositionInPool;
    //TODO CHeck if it crashes on NULL TexturePath
    if(TexturePath != NONE) {
        (*self)->ObjTexture = SDL_CreateTextureFromSurface(GfxRenderer, IMG_Load(TexturePath));
    }
    else {
        (*self)->ObjTexture = NONE;
    }
    (*self)->isHFlipped = FALSE;
    (*self)->isVFlipped = FALSE;
    (*self)->isPassable = TRUE;
    (*self)->isAlive = FALSE;
}

void deinitObject(GameObject2D **self) {
    if (*self != NONE) {
        deinitRigidBody2D(&(*self)->body2D);
        destroyTexture(&(*self)->ObjTexture);
        (*self)->ObjTexture = NONE;
        free(*self);
        *self = NONE;
    }
}

SDL_Rect *getObjectRect(GameObject2D *self) {
    return &self->ObjectRect;
}

SDL_Texture * getObjectTexture(GameObject2D *self) {
    return self->ObjTexture;
}

float getObjectRadius(GameObject2D *self) {
    return self->ObjectRadius;
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

void setPositionInPool(GameObject2D **self, uint8_t Position) {
    (*self)->PositionInObjectPool = Position;
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

void setAlive(GameObject2D **self, BOOL flag) {
    (*self)->isAlive = flag;
}

void setObjectTexture (GameObject2D **self, SDL_Texture *Texture) {
    (*self)->ObjTexture = Texture;
}

void updateBody2DTransform(GameObject2D **self, float NewX, float NewY) {
    setTransformX(&(*self)->body2D, NewX);
    setTransformY(&(*self)->body2D, NewY);
}

void updateObject(GameObject2D **self, float DeltaTime, Vector2D *Force, Vector2D *Friction) {
    updatePosition(&(*self)->body2D, DeltaTime, Force, Friction);
    (*self)->ObjectRect.x = (int) getTransformX((*self)->body2D);
    (*self)->ObjectRect.y = (int) getTransformY((*self)->body2D);
}


