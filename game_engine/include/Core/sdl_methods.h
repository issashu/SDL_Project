//
// Created by Iordan Tonchev on 6.10.21.
//

#ifndef SDL_GAME_SDL_METHODS_H
#define SDL_GAME_SDL_METHODS_H
#include <stdint.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "utils/defines.h"
#include "utils/vfx_tools/shapes.h"

//TODO Extract all struct objects in own header
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

//TODO Move to Main Engine code
struct Display{
    struct SDLWindow *Window;
    struct WindowConfig *DisplayConfig;
    struct Rectangle WindowShape;
};

int32_t initScreen(SDL_Window **Window, int32_t Width, int32_t Height);
int32_t initText();
int32_t initTextures();
int32_t initTimers();
int32_t initSFX();
void deinitGame(SDL_Window **Window, SDL_Surface **Image);

#endif //SDL_GAME_SDL_METHODS_H
