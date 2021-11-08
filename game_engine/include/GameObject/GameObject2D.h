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

GameObject2D * initObject(GameObject2D *self);
void deinitObject(GameObject2D **self);

SDL_Rect* getObjRect(GameObject2D *self);
BOOL getHorrizFlip(GameObject2D *self);
BOOL getVertFlip(GameObject2D *self);
BOOL getPassable(GameObject2D *self);
BOOL getAlive(GameObject2D *self);


void setHorrizFlip(GameObject2D *self, BOOL flag);
void setVertFlip(GameObject2D *self, BOOL flag);
void setPassable(GameObject2D *self, BOOL flag);
void setAlive(GameObject2D *self, BOOL flag);

void updateObject(GameObject2D **self, float DeltaTime, Vector2D *Force, Vector2D *Friction);

#endif //SDL_GAME_GAMEOBJECT2D_H
