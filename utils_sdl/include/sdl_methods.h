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
#include "defines.h"

struct SDLWindow{
    SDL_Window *Window;
    SDL_Surface *ScreenSurface;
    SDL_Surface *Image;
};

void initSDL();
int32_t initScreen(SDL_Window **Window, SDL_Surface **WindowSurface);
int32_t loadResources(SDL_Surface **Image, const STRING *ImagePath);
int32_t initText();
int32_t initTextures();
int32_t initTimers();
int32_t initSFX();
void drawGraphics(SDL_Window **Window, SDL_Surface **WindowSurface, SDL_Surface **Image);
void deinitGame(SDL_Window **Window, SDL_Surface **WindowSurface);

#endif //SDL_GAME_SDL_METHODS_H
