//
// Created by Iordan Tonchev on 9.11.21.
//

#include <SDL_rect.h>

#include "Core/Camera2D.h"
#include "Physics/Vector2D.h"
#include "utils/defines.h"
#include "Core/sdl_default_app_settings.h"



/*------------- PRIVATE: -----------------------*/

struct Camera2D{
    SDL_Rect ViewPoint;
    int32_t SceneWidth;
    int32_t SceneHeight;
};


/*------------- PUBLIC: -----------------------*/


void initCamera2D(Camera **self){
    *self = (Camera *)malloc(sizeof(struct Camera2D));
    (*self)->ViewPoint.x = 0;
    (*self)->ViewPoint.y = 0;
    (*self)->ViewPoint.w = WINDOW_WIDTH;
    (*self)->ViewPoint.h = WINDOW_HEIGHT;
    (*self)->SceneHeight = WINDOW_HEIGHT;
    (*self)->SceneWidth = WINDOW_WIDTH;
}

void deinitCamera2D(Camera **self){
    free(*self);
    *self = NONE;
}

void setCameraPosition(Camera **self, const int32_t *positionX, const int32_t *positionY) {
    (*self)->ViewPoint.x = (int32_t)*positionX;
    (*self)->ViewPoint.y = (int32_t)*positionY;
}

void moveCameraPosition(Camera **self, const float_t *positionX, const float_t *positionY, float_t DeltaTime){
    (*self)->ViewPoint.x += *positionX * DeltaTime;
    (*self)->ViewPoint.y += *positionY * DeltaTime;
}

void setCameraLimits (Camera **self, int32_t Width, int32_t Height){
    (*self)->SceneWidth = Width;
    (*self)->SceneHeight = Height;
}

SDL_Rect* getCameraViewPoint(Camera *self){
    return &self->ViewPoint;
}