//
// Created by Iordan Tonchev on 8.10.21.
//

#ifndef SDL_GAME_SHAPES_H
#define SDL_GAME_SHAPES_H

#include <stdint.h>
#include <stdio.h>

struct Point {
    int32_t x;
    int32_t y;
};

struct Rectangle {
    int32_t x;
    int32_t y;
    int32_t w;
    int32_t h;
};

int8_t isPointInRect(const struct Rectangle *shape, const struct Point *point);

#endif //SDL_GAME_SHAPES_H
