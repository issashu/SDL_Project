//
// Created by Iordan Tonchev on 9.11.21.
//

#include <SDL_rect.h>

#include "Core/Camera2D.h"
#include "Physics/Vector2D.h"
#include "utils/defines.h"



/*------------- PRIVATE: -----------------------*/

struct Camera2D{
    SDL_Rect ViewPoint;
    SDL_Point *Target;
    Vector2D Position;
    int32_t SceneWidth;
    int32_t SceneHeight;
};


/*------------- PUBLIC: -----------------------*/


void initCamera2D(Camera **self){
    *self = (Camera *)malloc(sizeof(struct Camera2D));
    (*self)->ViewPoint.h = 0;
    (*self)->ViewPoint.w = 0;
    (*self)->ViewPoint.y = 0;
    (*self)->ViewPoint.x = 0;
    (*self)->Target = NONE;
    initVector2D(&(*self)->Position);
    (*self)->SceneHeight = 0;
    (*self)->SceneWidth = 0;
}

void deinitCamera2D(Camera **self){
    deinitVector2D(&(*self)->Position);
    (*self)->Target = NONE;
    free(*self);
    *self = NONE;
}

void setCameraPosition(Camera **self, const SDL_Point *position){
    (*self)->Position.X = position->x;
    (*self)->Position.Y = position->y;
}

void moveCameraPosition(Camera **self, const SDL_Point *position, float_t DeltaTime){
    (*self)->Position.X += position->x * DeltaTime;
    (*self)->Position.Y += position->y * DeltaTime;
}

void setCameraTarget (Camera **self, const SDL_Point *target){
    (*self)->Target = target;
}

void setCameraLimits (Camera **self, int32_t Width, int32_t Height){
    (*self)->SceneWidth = Width;
    (*self)->SceneHeight = Height;
}

SDL_Rect* getCameraViewPoint(Camera **self){
    return &(*self)->ViewPoint;
}