//
// Created by Iordan Tonchev on 7.10.21.
//

#ifndef SDL_GAME_EVENTMANAGER_H
#define SDL_GAME_EVENTMANAGER_H

#include <stdio.h>
#include <stdint.h>
#include <utils/defines.h>
#include <Actors/PlayerCharacter.h>


//TODO Apply singleton
void playerEventHandler(BOOL *isRunning, playerActor *Player, float *DeltaTime);
void keyboardEvent(BOOL *isRunning, playerActor *Player, const u_int8_t *gameKeyStates, float *DeltaTime);

#endif //SDL_GAME_EVENTMANAGER_H
