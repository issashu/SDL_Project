//
// Created by Iordan Tonchev on 20.10.21.
//

#include <stdio.h>
#include <stdlib.h>

#include "Physics/Vector2D.h"
#include "Utils/include/Defines.h"

/*------------- PRIVATE: -----------------------*/


void setVector2D (Vector2D *self, double X, double Y) {
    self->X = X;
    self->Y = Y;
}

Vector2D sumVector2D(Vector2D *self, Vector2D *vec2){
    Vector2D result;
    initVector2D(&result);

    result.X = self->X + vec2->X;
    result.Y = self->Y + vec2->Y;

    return result;
}

Vector2D substVector2D(Vector2D *self, Vector2D *vec2){
    Vector2D result;
    initVector2D(&result);

    result.X = self->X - vec2->X;
    result.Y = self->Y - vec2->Y;

    return result;
}

Vector2D scalingVector2D(Vector2D *self, float scallar) {
    Vector2D scaledVector;
    initVector2D(&scaledVector);

    scaledVector.X = self->X * scallar;
    scaledVector.Y = self->Y * scallar;

    return scaledVector;
}

//FIXME Remove the dirty fix and remake variables as doubles to prevent printf from whining...
void debugVector2D(Vector2D *self){
    printf("The vector2D has values: x = %f and Y = %f\n", (double) self->X, (double) self->Y);
}

/*------------- PUBLIC: -----------------------*/

void initVector2D(Vector2D *self){
   // self = (Vector2D*)malloc(sizeof(struct Vector2D));
    self->X = 0;
    self->Y = 0;
    self->set = &setVector2D;
    self->sum = &sumVector2D;
    self->dif = &substVector2D;
    self->scale = &scalingVector2D;
    self->print = &debugVector2D;
}

void deinitVector2D(Vector2D *self) {
    if (self != NONE){
        free(self);
        self = NONE;
    }
}