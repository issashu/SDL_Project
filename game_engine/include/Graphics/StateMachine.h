/*
//
// Created by Iordan Tonchev on 7.11.21.
//

#ifndef SDL_GAME_STATEMACHINE_H
#define SDL_GAME_STATEMACHINE_H

#include "utils/defines.h"

typedef enum CharacterStates{
    IDLE_STATE,
    JUMPING,
    CROUCHING,
    DEAD,
    RUNNING_LEFT,
    RUNNING_RIGHT,
    ATTACKING
} StateFlags;

typedef struct StateMachine StateMachine;

StateMachine * initStateMachine (StateMachine *self);
void deinitStateMachine(StateMachine *self);
int32_t getState (StateMachine *self);
void setState(struct StateMachine *self, int32_t State);

#endif //SDL_GAME_STATEMACHINE_H
*/
