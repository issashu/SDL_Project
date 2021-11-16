//
// Created by Iordan Tonchev on 22.10.21.
//

#include <stdlib.h>

#include "utils/Log.h"
#include "utils/defines.h"
#include "GameObject/Transform2D.h"
#include "Physics/RigidBody2D.h"

//TODO Move defines to respective header
#define BODY_MASS 1.0f
#define WORLD_GRAVITY 1.45f

#define SPAWN_X 10
#define SPAWN_Y 50

/*------------- PRIVATE: -----------------------*/

struct RigidBody2D{
    Transform2D transform;
    float Mass;
    float appliedGravity;
    Vector2D appliedForce;
    Vector2D Friction;
    Vector2D Position;
    Vector2D Velocity;
    Vector2D Acceleration;
};

void setGravity(RigidBody2D *self, float newGravity){
    self->appliedGravity = newGravity;
}

void setMass(RigidBody2D *self, float newMass) {
    self->Mass = newMass;
}
//TODO Think about the need of unset force function or just use negative vector
void applyForce(RigidBody2D *self, Vector2D *Force) {
    self->appliedForce.X = Force->X;
    self->appliedForce.Y = Force->Y;
}

void applyFriction(RigidBody2D *self, Vector2D *Friction){
    self->Friction.X = Friction->X;
    self->Friction.Y = Friction->Y;
}

//Force+Friction = acc*mass (Using negative Friction for ice and option for vertical Friction)
void applyAcceleration(RigidBody2D *self) {
    self->Acceleration.X = (self->appliedForce.X - self->Friction.X) / self->Mass;
    self->Acceleration.Y = (self->appliedForce.Y - self->Friction.Y + self->appliedGravity) / self->Mass;
}

void setVelocity(RigidBody2D *self, float deltaTime) {
    if(self != NONE){
        self->Velocity = self->Velocity.scale(&self->Acceleration, deltaTime);
    }
    else{
        LOGERR("Setting velocity has failed!!");
    }
}

/*------------- PUBLIC: -----------------------*/

//FIXME Set the spawn location correctly w/o magic numbers
void initRigidBody2D(RigidBody2D **self, float SpawnX, float SpawnY) {
    *self = (RigidBody2D *)malloc(sizeof(struct RigidBody2D));
    (*self)->transform.X = SpawnX;
    (*self)->transform.Y = SpawnY;
    (*self)->Mass = BODY_MASS;
    (*self)->appliedGravity = WORLD_GRAVITY;
    initVector2D(&(*self)->appliedForce);
    initVector2D(&(*self)->Friction);
    initVector2D(&(*self)->Position);
    initVector2D(&(*self)->Velocity);
    initVector2D(&(*self)->Acceleration);
}

void deinitRigidBody2D(RigidBody2D **self) {
    if (*self != NONE) {
        free(*self);
        *self = NONE;
    }
}

float getMass(RigidBody2D *self) {
    return self->Mass;
}

float getGravity(RigidBody2D *self) {
    return self->appliedGravity;
}

float getTransformX(RigidBody2D *self) {
    return self->transform.X;
}

float getTransformY(RigidBody2D *self) {
    return self->transform.Y;
}

void setTransformX(RigidBody2D **self, float NewX) {
    (*self)->transform.X = NewX;
}

void setTransformY(RigidBody2D **self, float NewY) {
    (*self)->transform.Y = NewY;
}



//FIXME Move transform to GameObject and not RigidBody2D and use translate methods in transform
void updatePosition(RigidBody2D **self, float deltaTime, Vector2D *Force, Vector2D *Friction) {
    if(self != NONE){
        applyForce((*self), Force);
        applyFriction((*self), Friction);
        applyAcceleration((*self));
        setVelocity((*self), deltaTime);
        (*self)->Position = (*self)->Position.scale(&(*self)->Velocity, deltaTime);
        (*self)->transform.X += (*self)->Position.X;
        (*self)->transform.Y += (*self)->Position.Y;
    }
    else{
        LOGERR("Setting position has failed!!");
    }
}

