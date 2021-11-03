//
// Created by Iordan Tonchev on 22.10.21.
//

#ifndef SDL_GAME_SDL_CHARACTER_H
#define SDL_GAME_SDL_CHARACTER_H

#include "GameObject/GameObject2D.h"
#include "Physics/sdl_rigidBody2D.h"
#include "Graphics/sdl_transform2D.h"

//Enums are based on the sprite sheet, decrease by 1 when using in code
//Using common sprite sheet, thus enums are in character struct and not actor structs
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
// We can cast between base class and child class like that (since pointer will point to the first element,
// which being base class, will fit the memory correctly :) )
typedef struct CharacterActor {
    GameObject2D *Base2D;
    int8_t Health;
    int8_t Mana;
    u_int8_t stateFlags;
    BOOL isAlive;
    STRING Name;
    //TODO Add some stats and function pointers for methods
} Character;

void initCharacter(Character *self, STRING name, STRING texturePath);

#endif //SDL_GAME_SDL_CHARACTER_H
