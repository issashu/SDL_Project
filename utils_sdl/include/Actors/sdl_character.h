//
// Created by Iordan Tonchev on 22.10.21.
//

#ifndef SDL_GAME_SDL_CHARACTER_H
#define SDL_GAME_SDL_CHARACTER_H

#include "GameObject/sdl_game_object.h"

typedef struct CharacterActor{
    GameObject *base;
    STRING Name;
    int8_t Health;
    int8_t Mana;
    BOOL isAlive;
    u_int8_t stateFlags;
    //TODO Add some stats and function pointers for methods
} Character;

void initCharacter(Character *self, STRING name, STRING texturePath);

#endif //SDL_GAME_SDL_CHARACTER_H
