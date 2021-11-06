//
// Created by Iordan Tonchev on 3.11.21.
//

#ifndef SDL_GAME_TIMERS_H
#define SDL_GAME_TIMERS_H

/**
 *
 * @param lastTime - Last updated time/game-tick
 * @return Returns the calculated delta time between last update and current moment
 */
float getDeltaTime(uint32_t *lastTime);

#endif //SDL_GAME_TIMERS_H
