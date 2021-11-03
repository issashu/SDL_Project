//
// Created by Iordan Tonchev on 3.11.21.
//

#include <SDL_timer.h>
#include <math.h>
#include "Timers/Timers.h"

//FIXME Exchange for a variable to be passed in options
#define FPS 60
#define DESIRED_MAX_SPEED 1.5f

float getDeltaTime(uint32_t lastTime) {
    float deltaTime = 0.0f;
    deltaTime = (float)(SDL_GetTicks() - lastTime);

    if (deltaTime > DESIRED_MAX_SPEED){
        deltaTime = DESIRED_MAX_SPEED;
    }


    return deltaTime;
}
