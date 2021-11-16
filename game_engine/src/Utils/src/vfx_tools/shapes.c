//
// Created by Iordan Tonchev on 8.10.21.
//

#include "Utils/include/vfx_tools/shapes.h"
#include "Utils/include/Defines.h"

//TODO Make the check shape type independent. Need to rethink shape struct
int8_t isPointInRect(const struct Rectangle *shape, const struct Point *point){
    if ((point->x > shape->x) || (point->y > shape->y)){
        return FALSE;
    }
    return TRUE;
}
