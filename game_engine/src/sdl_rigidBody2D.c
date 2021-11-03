//
// Created by Iordan Tonchev on 22.10.21.
//

#include "utils/Log.h"
#include "utils/defines.h"
#include "Graphics/sdl_transform2D.h"
#include "Physics/sdl_rigidBody2D.h"
#include "Physics/sdl_vector2D.h"

//TODO Move defines to respective header
#define BODY_MASS 1.0f
#define WORLD_GRAVITY 9.8f

struct RigidBody2D{
    Transform2D *transform;
    float Mass;
    float appliedGravity;
    Vector2D appliedForce;
    Vector2D Friction;
    Vector2D Position;
    Vector2D Velocity;
    Vector2D Acceleration;
};

void initRigidBody2D(RigidBody2D *self) {
    self->transform->X = 0;
    self->transform->Y = 0;
    self->Mass = BODY_MASS;
    self->appliedGravity = WORLD_GRAVITY;
    initVector2D(&self->appliedForce);
    initVector2D(&self->Friction);
    initVector2D(&self->Position);
    initVector2D(&self->Velocity);
    initVector2D(&self->Acceleration);
}

inline float getMass(RigidBody2D *self) {return self->Mass;}

inline float getGravity(RigidBody2D *self) {return self->appliedGravity;}

void setGravity(RigidBody2D *self, float newGravity){
    self->appliedGravity = newGravity;
}

void setMass(RigidBody2D *self, float newMass) {
    self->Mass = newMass;
}
//TODO Think about the need of unset force function or just use negative vector
void applyForce(RigidBody2D *self, Vector2D *Force){
    self->appliedForce.X = Force->X;
    self->appliedForce.Y = Force->Y;
}

void applyFriction(RigidBody2D *self, Vector2D *Friction){
    self->Friction.X = Friction->X;
    self->Friction.Y = Friction->Y;
}

void applyAcceleration(RigidBody2D *self) {
    self->Acceleration.X = (self->appliedForce.X - self->Friction.X) / self->Mass;
    self->Acceleration.Y = (self->appliedForce.Y - self->Friction.Y + self->appliedGravity) / self->Mass;
}

//TODO Rethink how to simplify this: a method call another method inside
void setVelocity(RigidBody2D *self, float deltaTime) {
    if(self != NONE){
        self->Velocity = self->Velocity.scale(&self->Acceleration, deltaTime);
    }
    else{
        LOGERR("Setting velocity has failed!!");
    }
}

void setPosition(RigidBody2D *self, float deltaTime){
    if(self != NONE){
        self->Position = self->Position.scale(&self->Velocity, deltaTime);
        self->transform->X += self->Position.X;
        self->transform->Y += self->Position.Y;
    }
    else{
        LOGERR("Setting position has failed!!");
    }
}

