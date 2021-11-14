//
// Created by Iordan Tonchev on 21.10.21.
//

#ifndef SDL_GAME_GAMEOBJECT2D_H
#define SDL_GAME_GAMEOBJECT2D_H

#include <SDL.h>

#include "GameObject/GameObject2D.h"
#include "utils/defines.h"
#include "Physics/Vector2D.h"

typedef struct GameObject GameObject2D;

void initObject(GameObject2D **self, uint8_t PositionInPool, int32_t Width, int32_t Height, SDL_Renderer *GfxRenderer,
                char *TexturePath, float SpawnX, float SpawnY);
void deinitObject(GameObject2D **self);

SDL_Rect* getObjectRect(GameObject2D *self);
SDL_Texture * getObjectTexture(GameObject2D *self);
float getObjectRadius(GameObject2D *self);
BOOL getHorrizFlip(GameObject2D *self);
BOOL getVertFlip(GameObject2D *self);
BOOL getPassable(GameObject2D *self);
BOOL getAlive(GameObject2D *self);


void setHorrizFlip(GameObject2D *self, BOOL flag);
void setVertFlip(GameObject2D *self, BOOL flag);
void setPassable(GameObject2D *self, BOOL flag);
void setAlive(GameObject2D **self, BOOL flag);
void setObjectTexture (GameObject2D **self, SDL_Texture *Texture);
void updateBody2DTransform(GameObject2D **self, float NewX, float NewY);

void updateObject(GameObject2D **self, float DeltaTime, Vector2D *Force, Vector2D *Friction);

#endif //SDL_GAME_GAMEOBJECT2D_H
