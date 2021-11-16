//
// Created by Iordan Tonchev on 21.10.21.
//

#include "GameObject/Transform2D.h"

//TODO Check how to attach to game object in pure C.
// Using fake structs inside methods. Replace with real ones

void TranslateX(Transform2D *self, float x) {
   self->X += x;
}

void TranslateY(Transform2D *self, float y) {
    self->Y += y;
}

void Translate2D(float x, float y, Transform2D *self) {
    self->X += x;
    self->Y += y;
}