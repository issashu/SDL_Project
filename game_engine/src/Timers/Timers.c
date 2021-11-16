//
// Created by Iordan Tonchev on 3.11.21.
// Used https://hextobinary.com/unit/frequency/from/fps/to/fpms
//

#include <SDL_timer.h>
#include "Timers/Timers.h"

//TODO Cleanup the code and changes the FPS to a variable from settings
#define FPS 60
#define TARGET_DELTA_TIME 1.5f
#define MSECS_TO_SECS 1000.0f

float getDeltaTime(uint32_t *lastTime) {
    float deltaTime = 0.0f;
    uint32_t currentTIme = SDL_GetTicks();
    deltaTime = (float)(currentTIme - *lastTime)*(FPS/MSECS_TO_SECS);
    *lastTime = currentTIme;

    if (deltaTime > TARGET_DELTA_TIME){
        deltaTime = TARGET_DELTA_TIME;
    }

    return deltaTime;
}


