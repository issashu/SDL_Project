//
// Created by Iordan Tonchev on 8.10.21.
//

#include "vfx_tools/shapes.h"
#include "defines.h"

/*static const struct Point POINT_ZERO = {.x = 0, .y = 0};
static const struct Point POINT_UNDEFINED = {.x = 100000, .y = 100000 };
static const struct Rectangle RECT_ZERO = {.x = 0, .y = 0, .w = 0, .h = 0};
static const struct Rectangle RECT_UNDEFINED = {.x = 100000, .y = 100000, .w = 10000, .h = 10000};*/

//TODO Make the check shape type independent. Need to rethink shape struct
int8_t isPointInRect(const struct Rectangle *shape, const struct Point *point){
    if ((point->x > shape->x) || (point->y > shape->y)){
        return FALSE;
    }
    return TRUE;
}
