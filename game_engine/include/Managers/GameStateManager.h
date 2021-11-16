//
// Created by Iordan Tonchev on 13.11.21.
//

#ifndef SDL_GAME_GAMESTATEMANAGER_H
#define SDL_GAME_GAMESTATEMANAGER_H

#include <stdint.h>
#include <stdlib.h>

typedef struct GameStateManager {
    uint8_t (*switchState)(uint8_t);
    uint8_t(*getState)();
} GameStateManager;

GameStateManager* getGameStateManager();
void deinitGameStateManager();

#endif //SDL_GAME_GAMESTATEMANAGER_H
