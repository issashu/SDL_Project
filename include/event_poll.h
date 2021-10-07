//
// Created by Iordan Tonchev on 7.10.21.
//

#ifndef SDL_GAME_EVENT_POLL_H
#define SDL_GAME_EVENT_POLL_H

#include <stdio.h>
#include <SDL.h>
#include <SDL_events.h>
#include "include/defines.h"

int8_t eventHandler(SDL_Event** gameEvent);

#endif //SDL_GAME_EVENT_POLL_H
