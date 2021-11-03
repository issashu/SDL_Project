//
// Created by Iordan Tonchev on 7.10.21.
//

#ifndef SDL_GAME_EVENTMANAGER_H
#define SDL_GAME_EVENTMANAGER_H

#include <stdio.h>
#include <stdint.h>

//TODO Apply singleton
void eventHandler(int8_t *isRunning);
void keyboardEvent(int8_t *isRunning);

#endif //SDL_GAME_EVENTMANAGER_H
