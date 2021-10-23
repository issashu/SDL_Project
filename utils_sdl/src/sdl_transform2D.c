//
// Created by Iordan Tonchev on 21.10.21.
//

#include "Graphics/sdl_transform2D.h"

struct Transform2D {
    float X;
    float Y;
    void (*transX)(float);
    void (*transY)(float);
    void (*trans2D)(float, float);
};

//TODO Check how to attach to game object in pure C.
// Using fake structs inside methods. Replace with real ones

__attribute__((unused)) void TranslateX(float x) {
   struct Transform2D Point;
   Point.X += x;
}

__attribute__((unused)) void TranslateY(float y) {
    struct Transform2D Point;
    Point.Y += y;
}

__attribute__((unused)) void Translate2D(float x, float y) {
    struct Transform2D Point;
    Point.X += x;
    Point.Y += y;
}