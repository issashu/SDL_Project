//
// Created by Iordan Tonchev on 23.10.21.
//

#ifndef SDL_GAME_WINDOWMANAGER_H
#define SDL_GAME_WINDOWMANAGER_H

#include <utils/defines.h>

struct SDLWindow{
    SDL_Window *Window;
    UNUSED SDL_Surface *ScreenSurface;
    SDL_Surface *Image;
};

struct WindowConfig {
    //Window modes:
    //SDL_WINDOW_SHOWN - for windowed version
    //SDL_WINDOW_FULLSCREEN_DESKTOP - for fullscreen
    int32_t displayMode;
    int32_t windowWidth;
    int32_t windowHeight;
    struct Point windowPos;
    char *windowName;
};

#endif //SDL_GAME_WINDOWMANAGER_H
