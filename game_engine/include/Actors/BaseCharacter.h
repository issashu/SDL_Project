//
// Created by Iordan Tonchev on 22.10.21.
//

#ifndef SDL_GAME_BASECHARACTER_H
#define SDL_GAME_BASECHARACTER_H

#include <stdint.h>

#include "Physics/Vector2D.h"
#include "utils/defines.h"

/*
 * Enums are based on the sprite sheet.
 * Decrease by 1 when using in code
 *
 * Using common sprite sheet for both player and enemies,
 * thus enums are in base character struct and not actor structs
 */
enum animType {
    IDLE = 2,
    CROUCH = 10,
    RUN = 4,
    DASH = 13,
    JUMP = 9,
    ROLL = 12,
    CRAWL = 11,
    DIE = 18,
    TOTAL_ANIM_TYPES = 8
};

enum animFrames {
    IDLE_FRAMES = 7,
    CROUCH_FRAMES = 6,
    RUN_FRAMES = 8,
    DASH_FRAMES = 4,
    JUMP_FRAMES = 14,
    ROLL_FRAMES = 10,
    CRAWL_FRAMES = 8,
    DIE_FRAMES = 5
};

//TODO Make sure that base class structures are always first

typedef struct CharacterActor Character;

void initCharacter(Character *self, char *texturePath);
int32_t getHealth (Character *self);
int32_t getMana (Character *self);
STRING getSpriteSheet(Character *self);
void setHealth(Character *self, int32_t HP);
void takeDamage(Character *self, int32_t Dmg);
void healDamage(Character *self, int32_t Heal);
void moveCharacter(Character *self, float DeltaTime, Vector2D *Force, Vector2D *Friction);



#endif //SDL_GAME_BASECHARACTER_H
