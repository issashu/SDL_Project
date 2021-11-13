//
// Created by Iordan Tonchev on 9.11.21.
//

#ifndef SDL_GAME_CAMERA2D_H
#define SDL_GAME_CAMERA2D_H

typedef struct Camera2D Camera;
void initCamera2D(Camera **self, int32_t Width, int32_t Height);
void deinitCamera2D(Camera **self);
void setCameraPosition(Camera **self, int32_t positionX, int32_t positionY);
void moveCameraPosition(Camera **self, float_t positionX, float_t positionY, float_t DeltaTime);
void setCameraLimits (Camera **self, int32_t Width, int32_t Height);
SDL_Rect* getCameraViewPoint(Camera *self);
SDL_Texture **getCameraTexture(Camera *self);

#endif //SDL_GAME_CAMERA2D_H
