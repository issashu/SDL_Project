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
struct MonitorWindowCfg {
    //Window modes:
    //SDL_WINDOW_SHOWN - for windowed version
    //SDL_WINDOW_FULLSCREEN_DESKTOP - for fullscreen
    int32_t displayMode;
    int32_t windowWidth;
    int32_t windowHeight;
    struct Point windowPos;
    char *windowName;
};

struct SDLWindow{
    SDL_Window *Window;
    __attribute__((unused)) SDL_Surface *ScreenSurface;
    SDL_Surface *Image;
};

struct Display{
    struct SDLWindow *Window;
    struct MonitorWindowCfg *DisplayConfig;
    struct Rectangle WindowShape;
};

void initSDL();
int32_t initScreen(SDL_Window **Window);
//int32_t loadResources(SDL_Surface **Image, const STRING *ImagePath);
int32_t initText();
int32_t initTextures();
int32_t initTimers();
int32_t initSFX();
void drawGraphics(SDL_Renderer **Renderer, SDL_Texture *Texture);
void deinitGame(SDL_Window **Window, SDL_Surface **Image);

#endif //SDL_GAME_SDL_METHODS_H
