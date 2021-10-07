//
// Created by Iordan Tonchev on 6.10.21.
//

#ifndef SDL_GAME_SDL_METHODS_H
#define SDL_GAME_SDL_METHODS_H
#include <stdint.h>
#include <SDL.h>
#include "defines.h"

struct SDLWindow{
    SDL_Window *Window;
    SDL_Surface *ScreenSurface;
    SDL_Surface *Image;
};

void initSDL();
int32_t initScreen(SDL_Window **Window, SDL_Surface **WindowSurface);
int32_t loadResources(SDL_Surface **Image, const STRING *ImagePath);
void drawGraphics(SDL_Window **Window, SDL_Surface **WindowSurface, SDL_Surface **Image);
void deinitGame(SDL_Window **Window, SDL_Surface **WindowSurface);

#endif //SDL_GAME_SDL_METHODS_H
