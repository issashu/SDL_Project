//
// Created by Iordan Tonchev on 22.10.21.
//

#include <stdlib.h>

#include "Actors/BaseCharacter.h"
#include "utils/defines.h"

/*------------- PRIVATE: -----------------------*/

struct CharacterActor{
GameObject2D *Base2D;
StateFlags CharacterState;
int32_t Health;
int32_t Mana;
float AnimationSpeed;
STRING spriteSheet;
//TODO Add some stats and function pointers for methods
};

/*------------- PUBLIC: -----------------------*/

//FIXME Replace magic numbers
Character* initCharacter(Character *self, char *texturePath) {
    self = (Character*)malloc(sizeof(struct CharacterActor));
    self->Base2D = initObject(self->Base2D);
    self->CharacterState = IDLE_STATE;
    self->Health = 100;
    self->Mana = 100;
    self->AnimationSpeed = 150.0f;
    self->spriteSheet = texturePath;

    return self;
}

void deinitCharacter(Character *self) {
    if(self != NONE) {
        deinitObject(&self->Base2D);
        free(self);
        self = NONE;
    }
}

GameObject2D* getBaseObj (Character *self) {
    return self->Base2D;
}

int32_t getState (Character *self) {
    return self->CharacterState;
}

int32_t getHealth (Character *self) {
    return self->Health;
}

int32_t getMana (Character *self) {
    return self->Mana;
}

int32_t getAnimationSpeed (Character *self) {
    return self->AnimationSpeed;
}

STRING getSpriteSheet(Character *self) {
    return self->spriteSheet;
}

void setState(Character *self, int32_t State){
    self->CharacterState = State;
}

void setHealth(Character *self, int32_t HP){
    self->Health = HP;
}

void takeDamage(Character *self, int32_t Dmg) {
    self->Health -=Dmg;
}

void healDamage(Character *self, int32_t Heal) {
    self->Health +=Heal;
}

void setAnimationSpeed(Character **self, int32_t speed) {
    (*self)->AnimationSpeed = speed;
}

void moveCharacter(Character *self, float DeltaTime, Vector2D *Force, Vector2D *Friction) {
    updateObject(&self->Base2D,DeltaTime, Force, Friction);
}