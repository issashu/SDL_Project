//
// Created by Iordan Tonchev on 23.10.21.
//

#include <stdint.h>
#include <SDL.h>
#include <SDL_video.h>
#include "Utils/include/Defines.h"
#include "Utils/include/Log.h"
#include "Utils/include/vfx_tools/shapes.h"
#include "Managers/WindowManager.h"

struct UNUSED WindowConfig {
    //Window modes:
    //SDL_WINDOW_SHOWN - for windowed version
    //SDL_WINDOW_FULLSCREEN_DESKTOP - for fullscreen
    int32_t displayMode;
    int32_t windowWidth;
    int32_t windowHeight;
    struct Point windowPos;
    char *windowName;
};

int32_t initScreen(SDL_Window **Window, int32_t Width, int32_t Height) {
    if (SDL_Init(SDL_INIT_VIDEO) != SUCCESS) {
        LOGERR("SDL_Init_VIDEO() failed! Reason: %s", SDL_GetError());
        //TODO Add filename, path and line number to the logger
        //TODO Why do we use a macro in LOGGER?
        return FAILURE;
    }
   ;
//TODO Use the config struct
    *Window = SDL_CreateWindow("Metroidvania", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, \
                                Width, Height, SDL_WINDOW_SHOWN);
    if (*Window == NULL) {
        LOGERR("SDL_CreateWindow failed! Reason: %s", SDL_GetError());
        //TODO Add filename, path and line number to the logger
        return FAILURE;
    }

    return SUCCESS;
}