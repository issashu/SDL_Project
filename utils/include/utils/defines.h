//
// Created by Iordan Tonchev on 6.10.21.
//

#ifndef SDL_GAME_DEFINES_H
#define SDL_GAME_DEFINES_H

#define SUCCESS 0
#define FAILURE 1
#define HALF 0.5f
#define TRUE 1
#define FALSE 0
#define BOOL int8_t
#define NONE ((void*)0)
#define STRING char*
#define UNUSED __attribute__((unused))

enum ObjectTypes{
    BASIC_PLATFORM = 1,
    FALL_THROUGH_TRAP,
    SPIKE_TRAP,
    HEALING_POTION,
    MANA_POTION,
    BONUS_POINTS_ITEM,
    GENERIC_GAME_OBJECT
};

#endif //SDL_GAME_DEFINES_H
