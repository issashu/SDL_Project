//
// Created by Iordan Tonchev on 1.11.21.
//

#include <stdint.h>
#include <stdlib.h>

#include "GameObject/ObjectPool.h"
#include "utils/defines.h"

/*------------- PRIVATE: -----------------------*/

#define OBJECT_COUNT 20
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

static struct Vector *ObjectContainer = NONE;
static ObjectPool *self = NONE;
//TODO Add Bitfields and bitwise object tagging
UNUSED static uint64_t ObjectFlags = 0;

static void flagObject (GameObject2D *object);
void addObjects (struct Vector *pool, GameObject2D *object);
GameObject2D* pullObject (uint8_t position);

/*------------- PUBLIC: -----------------------*/
//TODO Decide about hard-coding the object number and usage of flag (if needed at all)
ObjectPool* getObjectPool () {
    if (self == NONE) {
        self = (ObjectPool*) malloc(sizeof(struct ObjectPool2D));
        initVector(ObjectContainer, OBJECT_COUNT);
        self->StashObject = &addObjects;
        self->TakeOutObject = &pullObject;
    }
    return self;
}

void deleteObjectPool () {
    if (self != NONE) {
        freeVector(ObjectContainer);
        free(self);
        self = NONE;
    }
}


/*------------- IMPLEMENTATION: -----------------------*/

void addObjects (struct Vector *pool, GameObject2D *object) {
    pushElementVector(pool,(void*)object);
    flagObject(object);
}

GameObject2D* pullObject (uint8_t position) {
    GameObject2D *object = NULL;
    object = (GameObject2D*) getElementVector(ObjectContainer,position);
    if (getAlive(object) == FALSE) {
        return object;
    }
    return NONE;
}

void flagObject (GameObject2D *object) {
    setAlive(&object, TRUE);
}

