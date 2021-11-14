//
// Created by Iordan Tonchev on 9.11.21.
//

#include <SDL_render.h>

#include "Core/Camera2D.h"


/*------------- PRIVATE: -----------------------*/

struct Camera2D{
    GameObject2D *BaseObject;
    int32_t SceneWidth;
    int32_t SceneHeight;
};


/*------------- PUBLIC: -----------------------*/

void
initCamera2D(Camera **self, int32_t Width, int32_t Height, SDL_Renderer *GfxRenderer, char *TexturePath, float SpawnX,
             float SpawnY) {
    *self = (Camera *)malloc(sizeof(struct Camera2D));
    initObject(&(*self)->BaseObject, 0, Width, Height, GfxRenderer, TexturePath, SpawnX, SpawnY);
    (*self)->SceneHeight = Width;
    (*self)->SceneWidth = Height;
}

void deinitCamera2D(Camera **self){
    if (*self != NONE){
        deinitObject(&(*self)->BaseObject);
        free(*self);
        *self = NONE;
    }
}

//TODO Add setObjectRect method and see the float to int BS
void setCameraPosition(Camera **self, int32_t positionX, int32_t positionY) {
    getObjectRect((*self)->BaseObject)->x= positionX;
    getObjectRect((*self)->BaseObject)->y = positionY;
}

void moveCameraPosition(Camera **self, float_t positionX, float_t positionY, float_t DeltaTime){
    getObjectRect((*self)->BaseObject)->x += positionX * DeltaTime;
    getObjectRect((*self)->BaseObject)->y += positionY * DeltaTime;
}

void setCameraLimits (Camera **self, int32_t Width, int32_t Height){
    (*self)->SceneWidth = Width;
    (*self)->SceneHeight = Height;
}

SDL_Rect* getCameraViewPoint(Camera *self){
    return getObjectRect(self->BaseObject);
}

SDL_Texture * getCameraTexture(Camera *self){
    return getObjectTexture(self->BaseObject);
}

GameObject2D* getCameraObject(Camera *self) {
    return self->BaseObject;
}