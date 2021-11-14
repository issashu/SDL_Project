//
// Created by Iordan Tonchev on 22.10.21.
//

#include <stdlib.h>

#include <SDL_render.h>
#include <SDL_events.h>
#include "Actors/BaseCharacter.h"
#include "utils/defines.h"

/*------------- PRIVATE: -----------------------*/

struct CharacterActor {
GameObject2D *Base2D;
StateFlags CharacterState;
SDL_Event CharacterEvent;
int32_t Health;
int32_t Mana;
float AnimationSpeed;
STRING spriteSheet;
//TODO Add some stats and function pointers for methods
};

/*------------- PUBLIC: -----------------------*/

//Added event to struct in order to control the AI via submitted events
//FIXME Replace magic numbers
void initCharacter(Character **self, char *texturePath, SDL_Renderer *GfxRenderer) {
    *self = (Character*)malloc(sizeof(struct CharacterActor));
    (*self)->CharacterState = IDLE_STATE;
    (*self)->CharacterEvent.type = SDL_USEREVENT;
    (*self)->Health = 100;
    (*self)->Mana = 100;
    (*self)->AnimationSpeed = 150.0f;
    (*self)->spriteSheet = texturePath;
    initObject(&(*self)->Base2D, 0, SPRITE_WIDTH, SPRITE_HEIGHT, GfxRenderer, (*self)->spriteSheet);
}

void deinitCharacter(Character **self) {
    if(*self != NONE) {
        deinitObject(&(*self)->Base2D);
        free(*self);
        *self = NONE;
    }
}

GameObject2D* getBaseObj (Character *self) {
    return self->Base2D;
}

SDL_Event* getCharacterEvent(Character *self) {
    return &self->CharacterEvent;
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

float_t getAnimationSpeed (Character *self) {
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

void moveCharacter(Character *self, const float *DeltaTime,
                   Vector2D *Force, Vector2D *Friction) {
    updateObject(&self->Base2D, *DeltaTime, Force, Friction);
}