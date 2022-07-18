//
// Created by Iordan Tonchev on 1.11.21.
//

#include <stdint.h>
#include <stdlib.h>

#include "GameObject/ObjectPool.h"
#include "GameObject/Platforms/BasePlatform2D.h"
#include "Utils/include/Defines.h"

/*------------- PRIVATE: -----------------------*/

#define OBJECT_COUNT 20
#define CHECK_BIT(var, pos) ((var) & (1<<(pos)))

static ObjectPool *self = NONE;

static struct Vector ObjectContainer;
static size_t PoolSize = OBJECT_COUNT;

//TODO Implement Object type database (RTTI?) that is not hard-coded (or just implement uint8_t Vector type maybe)
static uint8_t* ObjectLibraryCards;


//TODO Add Bitfields and learn/train bitwise object tagging
UNUSED static uint64_t ObjectFlags = 0;

static void flagObject(GameObject2D *object);

size_t addObjects(void *object, uint8_t ObjectType);

void removeObject(uint8_t position);

void * pullObject(uint8_t position);

void resizeObjectLibraryCards(uint32_t NewSize);

/*------------- PUBLIC: -----------------------*/
//TODO Decide about hard-coding the object initial number and usage of flag (if needed at all)
ObjectPool *getObjectPool() {
    if (self == NONE) {
        self = (ObjectPool *) malloc(sizeof(struct ObjectPool2D));
        ObjectLibraryCards = calloc(OBJECT_COUNT, sizeof(uint8_t));
        initVector(&ObjectContainer, OBJECT_COUNT);
        self->StashObject = &addObjects;
        self->TakeOutObject = &pullObject;
        self->TrashObject = &removeObject;
    }
    return self;
}

void deleteObjectPool() {
    if (self != NONE) {
        freeVector(&ObjectContainer);
        free(ObjectLibraryCards);
        free(self);
        self = NONE;
    }
}

/*------------- IMPLEMENTATION: -----------------------*/

size_t addObjects(void *object, uint8_t ObjectType) {
    size_t PositionTicket = 0;
    pushElementVector(&ObjectContainer, object);
    PositionTicket = getSizeVector(&ObjectContainer);
    ObjectLibraryCards[PositionTicket] = ObjectType;
    if (PositionTicket >= PoolSize - 1) {
        size_t NewSize = PositionTicket + 5;
        resizeObjectLibraryCards(NewSize);
        PoolSize = NewSize;
    }

    return PositionTicket;
}

void* pullObject(uint8_t position) {
    if (ObjectLibraryCards[position] != 0) {
        switch (ObjectLibraryCards[position]) {
            case BASIC_PLATFORM: {
              BasePlatform2D* tmpObject = getElementVector(&ObjectContainer, position-1);
              return tmpObject;
            }
            case FALL_THROUGH_TRAP:
                break;
            case SPIKE_TRAP:
                break;
            case HEALING_POTION:
                break;
            case MANA_POTION:
                break;
            case BONUS_POINTS_ITEM:
                break;
            case GENERIC_GAME_OBJECT:
            default:
                break;
        }
    }
    return NONE;
}

UNUSED void flagObject(GameObject2D *object) {
    setAlive(&object, TRUE);
}

//FIXME Rework this method to something more useful...
void removeObject(uint8_t position) {
    free(getElementVector(&ObjectContainer, position));
    ObjectLibraryCards[position] = 0;
}

void resizeObjectLibraryCards(uint32_t NewSize) {
    ObjectLibraryCards = realloc(ObjectLibraryCards, NewSize);
}
