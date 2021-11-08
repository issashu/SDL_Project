/*
//
// Created by Iordan Tonchev on 7.11.21.
//

#include <SDL.h>
#include "Graphics/StateMachine.h"
#include "utils/defines.h"

struct StateMachine {
    StateFlags CharacterState;
};

StateMachine* initStateMachine (StateMachine *self) {
    self = (StateMachine *)malloc(sizeof(struct StateMachine));
    self->CharacterState = IDLE_STATE;

    return self;
}

void deinitStateMachine(StateMachine *self){
    if (self != NONE) {
        free(self);
        self = NONE;
    }
}

int32_t getState (StateMachine *self) {
    return self->CharacterState;
}

void setState(struct StateMachine *self, int32_t State){
    self->CharacterState = State;
}*/
