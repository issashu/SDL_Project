//
// Created by Iordan Tonchev on 6.11.21.
//


#include <SDL_rect.h>
#include <math.h>
#include "Managers/CollisionManager.h"

#define HALF 0.5f

/*------------- PRIVATE: -----------------------*/
static CollisionManager2D *self = NONE;

BOOL areObjectsColliding(GameObject2D *FirstObject, GameObject2D *SecondObject);

SDL_Rect ObjectsIntersectionRect(GameObject2D *FirstObject, GameObject2D *SecondObject);

uint8_t ObjectsIntersectionSide(GameObject2D *FirstObject, GameObject2D *SecondObject, int32_t *Overlap);

/*------------- PUBLIC: -----------------------*/
CollisionManager2D *getCollisionManager() {
    if (self == NONE) {
        self = (CollisionManager2D *) malloc(sizeof(struct CollisionManager));
        self->CheckCollision = &areObjectsColliding;
        self->getIntersectionRect = &ObjectsIntersectionRect;
        self->getIntersactionSide = &ObjectsIntersectionSide;
    }
    return self;
}

void deinitCollisionManager() {
    if (self != NONE) {
        free(self);
        self = NONE;
    }
}


/*------------- IMPLEMENTATION: -----------------------*/

BOOL areObjectsColliding(GameObject2D *FirstObject, GameObject2D *SecondObject) {
    SDL_Point CenterFirstObject = {.x = 0, .y = 0};
    SDL_Point CenterSecondObject = {.x = 0, .y = 0};
    float Hypotenuse = 0.0f;
    float SumObjRadiuses = 0.0f;

    CenterFirstObject.x = ((getObjectRect(FirstObject)->w + getObjectRect(FirstObject)->x) * HALF);
    CenterFirstObject.y = ((getObjectRect(FirstObject)->h + getObjectRect(FirstObject)->y) * HALF);

    CenterSecondObject.x = ((getObjectRect(SecondObject)->w + getObjectRect(SecondObject)->x) * HALF);
    CenterSecondObject.y = ((getObjectRect(SecondObject)->h + getObjectRect(SecondObject)->y) * HALF);

    //Pythagoras: c = sqrt(a^2 + b^2)
    Hypotenuse = sqrtf(powf((CenterFirstObject.x - CenterSecondObject.x), 2) +
                       powf((CenterFirstObject.y - CenterSecondObject.y), 2));

    SumObjRadiuses = getObjectRadius(FirstObject) + getObjectRadius(SecondObject);

    if (Hypotenuse <= SumObjRadiuses) {
        return TRUE;
    }

    return FALSE;
}

SDL_Rect ObjectsIntersectionRect(GameObject2D *FirstObject, GameObject2D *SecondObject) {
    SDL_Rect result;
    SDL_IntersectRect(getObjectRect(FirstObject), getObjectRect(SecondObject), &result);

    return result;
}

//TODO Hardcode Player always FirstObject
uint8_t ObjectsIntersectionSide(GameObject2D *FirstObject, GameObject2D *SecondObject, int32_t *Overlap) {
    SDL_Rect *First = getObjectRect(FirstObject);
    SDL_Rect *Second = getObjectRect(SecondObject);
    SDL_Rect IntersectionRect = {.x =0, .y = 0, .w = 0, .h = 0};

    if (SDL_IntersectRect(First, Second, &IntersectionRect)) {
        if (IntersectionRect.w > IntersectionRect.h) {
            *Overlap = IntersectionRect.h;
            if (First->y + (First->h/2) <= Second->y) {
                return SIDE_UP;
            } else {
                return SIDE_DOWN;
            }
        } else {
            *Overlap = IntersectionRect.w;
            if (First->x + First->w/2 <= Second->x) {
                return SIDE_LEFT;
            } else {
                return SIDE_RIGHT;
            }
        }
    }
    return NO_COLLISION;
}

    /*if (SDL_HasIntersection(First, Second)) {
        if ((First->x + First->w) = Second->x &&)
            return SIDE_LEFT;
        if ((First->x + First->w) >= Second->x)
            return SIDE_UP;
        if ((Second->x + Second->w) <= First->x)
            return SIDE_RIGHT;
        if ((Second->y + Second->h) <= First->y)
            return SIDE_DOWN;
    }*/


