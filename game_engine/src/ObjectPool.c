//
// Created by Iordan Tonchev on 1.11.21.
//

#include <stdint.h>
#include <stdlib.h>

#include "GameObject/ObjectPool.h"
#include "GameObject/GameObject2D.h"
#include "utils/containers/Vector.h"
#include "utils/defines.h"


#define OBJECT_COUNT 50
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

//TODO Decide about hardcoding the object number
struct ObjectPool{
    struct Vector *GameObjects;
    int8_t UsedFlags;
};

void initiateObjectPool (ObjectPool *pool){
    pool = malloc(sizeof(struct ObjectPool));
    pool->UsedFlags = 0;
    initVector(pool->GameObjects, OBJECT_COUNT);
}

void addObjects (ObjectPool *pool, GameObject2D *object) {
    pushElementVector(pool->GameObjects,(void*)object);
}

//TODO Check if Vector would allocate space for each object
GameObject2D* pullObject (ObjectPool *pool, int8_t position) {
    GameObject2D *object = NULL;
    if (CHECK_BIT(pool->UsedFlags, position) == FALSE){
        object = (GameObject2D*) getElementVector(pool->GameObjects,position);
    }
    return object;
}

void flagObject (ObjectPool *pool, int8_t position){
    pool->UsedFlags = (1 << position) | pool->UsedFlags;
}

