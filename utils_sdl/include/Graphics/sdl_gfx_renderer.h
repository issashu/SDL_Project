//
// Created by Iordan Tonchev on 10.10.21.
//

#ifndef SDL_GAME_SDL_GFX_RENDERER_H
#define SDL_GAME_SDL_GFX_RENDERER_H

//TODO Change the enum to be used in the final game or remove
#include <SDL.h>

#include "Core/sdl_methods.h"
#include "utils/containers/Vector.h"
#include "utils/Log.h"

enum ImageSurfaces{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

BOOL loadSurfaces(struct Vector *objTextures);
BOOL initRenderer(SDL_Window* Window, SDL_Renderer** Renderer);
BOOL setTexture(SDL_Surface* Image, SDL_Texture** Texture, SDL_Renderer *Renderer);

#endif //SDL_GAME_SDL_GFX_RENDERER_H
