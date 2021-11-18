//
// Created by Iordan Tonchev on 22.10.21.
//

#ifndef SDL_GAME_BASECHARACTER_H
#define SDL_GAME_BASECHARACTER_H

#include <stdint.h>

#include "Physics/Vector2D.h"
#include "Utils/include/Defines.h"
#include "GameObject/GameObject2D.h"

/*
 * Enums and defines are based on the sprite sheet.
 * Decrease by 1 when using in code
 *
 * Using common sprite sheet for both player and enemies,
 * thus enums and defines are in base character struct and not in each actor structs
 * as it normally should be.
 */

#define SPRITE_WIDTH 96
#define SPRITE_HEIGHT 84


enum animType {
    IDLE = 2,
    CROUCH = 10,
    RUN = 4,
    DASH = 13,
    JUMP = 9,
    ROLL = 12,
    CRAWL = 11,
    DIE = 18,
    ATTACK = 6,
    TOTAL_ANIM_TYPES = 9
};

enum animFrames {
    IDLE_FRAMES = 7,
    CROUCH_FRAMES = 6,
    RUN_FRAMES = 8,
    DASH_FRAMES = 4,
    JUMP_FRAMES = 14,
    ROLL_FRAMES = 10,
    CRAWL_FRAMES = 8,
    DIE_FRAMES = 5,
    ATTACK_FRAMES = 6
};

typedef enum CharacterStates{
    IDLE_STATE,
    JUMPING_UP,
    JUMPING_DOWN,
    JUMPING_RIGHT,
    JUMPING_LEFT,
    CROUCHING,
    CRAWLING_RIGHT,
    CRAWLING_LEFT,
    RUNNING_LEFT,
    RUNNING_RIGHT,
    ATTACKING,
    DEAD = 38
} StateFlags;

//TODO Make sure that base class structures are always first

typedef struct CharacterActor Character;

void initCharacter(Character **self, char *texturePath, SDL_Renderer *GfxRenderer, float SpawnX, float SpawnY);
void deinitCharacter(Character **self);

GameObject2D* getBaseObj (Character *self);
SDL_Event* getCharacterEvent(Character *self);
int32_t getState (Character *self);
int32_t getHealth (Character *self);
int32_t getMana (Character *self);
float_t getAnimationSpeed (Character *self);
STRING getSpriteSheet(Character *self);

void setState(Character *self, int32_t State);
void setHealth(Character *self, int32_t HP);
void takeDamage(Character *self, int32_t Dmg);
void healDamage(Character *self, int32_t Heal);
void setAnimationSpeed(Character **self, int32_t speed);

void moveCharacter(Character *self, const float *DeltaTime, Vector2D *Force, Vector2D *Friction);

#endif //SDL_GAME_BASECHARACTER_H
