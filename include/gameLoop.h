//
// Created by Iordan Tonchev on 9.10.21.
//

#ifndef SDL_GAME_GAMELOOP_H
#define SDL_GAME_GAMELOOP_H

#include <stdint.h>
#include <stdio.h>
#include "sdl_command.h"
#include "sdl_event_handler.h"
//TODO Stupid fix, must remove
#define BOOL int8_t

BOOL gameLoop();

#endif //SDL_GAME_GAMELOOP_H
