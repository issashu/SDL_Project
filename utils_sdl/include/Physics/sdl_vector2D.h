//
// Created by Iordan Tonchev on 20.10.21.
//

#ifndef SDL_GAME_SDL_VECTOR2D_H
#define SDL_GAME_SDL_VECTOR2D_H

typedef struct Vector2D {
    float X;
    float Y;
    //void (*init)(struct Vector2D *);
    void (*set)(struct Vector2D *, double, double);
    struct Vector2D (*sum)(struct Vector2D *, struct Vector2D *);
    struct Vector2D (*dif)(struct Vector2D *, struct Vector2D *);
    struct Vector2D (*scale)(struct Vector2D *, float);
    void (*print)(struct Vector2D *);
} Vector2D;

//TODO Find a way NOT to have stand alone constructor and have it inside the class
void initVector2D(Vector2D *self);

#endif //SDL_GAME_SDL_VECTOR2D_H
