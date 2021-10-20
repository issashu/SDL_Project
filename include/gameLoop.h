//
// Created by Iordan Tonchev on 9.10.21.
//

#ifndef SDL_GAME_GAMELOOP_H
#define SDL_GAME_GAMELOOP_H

#include <stdint.h>
#include <stdio.h>
#include "utils_sdl/include/Core/sdl_command.h"
#include "utils_sdl/include/Core/sdl_event_handler.h"
//TODO Stupid fix, must remove
#define BOOL int8_t

BOOL gameLoop();

#endif //SDL_GAME_GAMELOOP_H
