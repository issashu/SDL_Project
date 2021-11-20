//
// Created by Iordan Tonchev on 22.10.21.
//

#ifndef SDL_GAME_RIGIDBODY2D_H
#define SDL_GAME_RIGIDBODY2D_H

#include "Physics/Vector2D.h"

typedef struct RigidBody2D RigidBody2D;

void initRigidBody2D(RigidBody2D **self, float SpawnX, float SpawnY);
void deinitRigidBody2D(RigidBody2D **self);
UNUSED inline float getMass(RigidBody2D *self);
UNUSED inline float getGravity(RigidBody2D *self);
float getTransformX(RigidBody2D *self);
float getTransformY(RigidBody2D *self);
void setTransformX(RigidBody2D **self, float NewX);
void setTransformY(RigidBody2D **self, float NewY);
void updatePosition(RigidBody2D **self, float deltaTime, Vector2D *Force, Vector2D *Friction);

#endif //SDL_GAME_RIGIDBODY2D_H
