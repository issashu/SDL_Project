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
#define BOOL uint8_t
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

enum CollisionSides {
    NO_COLLISION = 0,
    SIDE_UP,
    SIDE_RIGHT,
    SIDE_DOWN,
    SIDE_LEFT,
    ALL_SIDES
};

enum GameStates {
    NO_STATE = 0,
    MAIN_SCREEN,
    MAIN_GAME,
    EXIT_GAME,
    ALL_STATES
};

#endif //SDL_GAME_DEFINES_H
