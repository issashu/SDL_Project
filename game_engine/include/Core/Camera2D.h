//
// Created by Iordan Tonchev on 9.11.21.
//

#ifndef SDL_GAME_CAMERA2D_H
#define SDL_GAME_CAMERA2D_H

typedef struct Camera2D Camera;
void initCamera2D(Camera **self);
void deinitCamera2D(Camera **self);
void setCameraPosition(Camera **self, const SDL_Point *position);
void moveCameraPosition(Camera **self, const SDL_Point *position, float_t DeltaTime);
void setCameraTarget (Camera **self, const SDL_Point *target);
void setCameraLimits (Camera **self, int32_t Width, int32_t Height);
SDL_Rect* getCameraViewPoint(Camera **self);

#endif //SDL_GAME_CAMERA2D_H
