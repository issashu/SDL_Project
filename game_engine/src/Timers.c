//
// Created by Iordan Tonchev on 3.11.21.
//

#include <SDL_timer.h>
#include "Timers/Timers.h"

//TODO Cleanup the code
#define DESIRED_MAX_SPEED 1/60
#define MSECS_TO_SECS 1000.0f

float getDeltaTime(uint32_t *lastTime) {
    float deltaTime = 0.0f;
    uint32_t currentTIme = SDL_GetTicks();
    deltaTime = (float)(currentTIme - *lastTime)/MSECS_TO_SECS;
    *lastTime = currentTIme;

    if (deltaTime < (DESIRED_MAX_SPEED)){
        deltaTime = (DESIRED_MAX_SPEED);
    }

    return deltaTime;
}


