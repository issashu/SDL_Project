//
// Created by Iordan Tonchev on 10.10.21.
//

#ifndef SDL_GAME_GFXRENDERER_H
#define SDL_GAME_GFXRENDERER_H

//TODO Change the enum to be used in the final game or remove
#include <SDL.h>

#include "Core/sdl_methods.h"
#include "utils/containers/Vector.h"
#include "utils/Log.h"



BOOL loadSurfaces(struct Vector *objTextures);
BOOL initRenderer(SDL_Window* Window, SDL_Renderer** Renderer);
void drawStatic(SDL_Renderer **Renderer, SDL_Texture *Texture);
void
drawAnimation(SDL_Renderer **Renderer, SDL_Texture *Texture, int32_t animType, int32_t firstFrame, int32_t animSpeed,
              int transX, int transY, int Width, int Height, BOOL vFlip, BOOL hFlip);

#endif //SDL_GAME_GFXRENDERER_H
