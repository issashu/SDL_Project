//
// Created by Iordan Tonchev on 10.10.21.
//

#ifndef SDL_GAME_GRAPHICSRENDERER2D_H
#define SDL_GAME_GRAPHICSRENDERER2D_H

//TODO Change the enum to be used in the final game or remove
#include <SDL.h>

#include "Core/sdl_methods.h"
#include "Utils/include/containers/Vector.h"
#include "Utils/include/Log.h"


BOOL loadSurfaces(struct Vector *objTextures, STRING TexturePath);
void unloadSurfaces(struct Vector *objTextures);
BOOL initRenderer(SDL_Window* Window, SDL_Renderer** Renderer);
void drawStatic(SDL_Renderer **Renderer, SDL_Texture *Texture, SDL_Rect *SrcRect, SDL_Rect *DstRect);
void drawAnimation(SDL_Renderer **Renderer, const SDL_Rect *targetFrame, SDL_Texture *Texture, int32_t animType,
                   int32_t firstFrame, float animSpeed, int Width, int Height, BOOL hFlip, float DeltaTime);
void drawTimedAnimation(SDL_Renderer **Renderer, const SDL_Rect *targetFrame, SDL_Texture *Texture, int32_t animType,
                        int32_t firstFrame, int32_t MaxFrames, float animSpeed, int Width, int Height, BOOL hFlip,
                        int32_t Timer, float DeltaTime);
void clearRenderer(SDL_Renderer **Renderer);
void presentRenderer(SDL_Renderer *Renderer);
void destroyRenderer(SDL_Renderer **Renderer);

#endif //SDL_GAME_GRAPHICSRENDERER2D_H
