//
// Created by Iordan Tonchev on 10.10.21.
//

#ifndef SDL_GAME_GRAPHICSRENDERER2D_H
#define SDL_GAME_GRAPHICSRENDERER2D_H

//TODO Change the enum to be used in the final game or remove
#include <SDL.h>

#include "Core/sdl_methods.h"
#include "utils/containers/Vector.h"
#include "utils/Log.h"



BOOL loadSurfaces(struct Vector *objTextures);
BOOL initRenderer(SDL_Window* Window, SDL_Renderer** Renderer);
void drawStatic(SDL_Renderer **Renderer, SDL_Texture *Texture);
void drawAnimation(SDL_Renderer **Renderer, SDL_Texture *Texture, int32_t animType, int32_t firstFrame, float animSpeed,
                   int transX, int transY, int Width, int Height, BOOL hFlip, float DeltaTime);
void destroyRenderer(SDL_Renderer **Renderer);

#endif //SDL_GAME_GRAPHICSRENDERER2D_H
