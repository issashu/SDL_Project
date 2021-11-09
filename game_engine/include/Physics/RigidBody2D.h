//
// Created by Iordan Tonchev on 22.10.21.
//

#ifndef SDL_GAME_RIGIDBODY2D_H
#define SDL_GAME_RIGIDBODY2D_H

#include "Physics/Vector2D.h"

typedef struct RigidBody2D RigidBody2D;

void initRigidBody2D(RigidBody2D **self);
void deinitRigidBody2D(RigidBody2D **self);
inline float getMass(RigidBody2D *self);
inline float getGravity(RigidBody2D *self);
void updatePosition(RigidBody2D **self, float deltaTime, Vector2D *Force, Vector2D *Friction);

#endif //SDL_GAME_RIGIDBODY2D_H
