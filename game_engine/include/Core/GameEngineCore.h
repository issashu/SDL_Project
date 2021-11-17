//
// Created by Iordan Tonchev on 8.10.21.
//

#ifndef SDL_GAME_GAMEENGINECORE_H
#define SDL_GAME_GAMEENGINECORE_H
#include <stdint.h>
#include <stdio.h>
#include "GameObject/GameObject2D.h"
#include "Actors/BaseCharacter.h"
#include "Actors/PlayerCharacter.h"
#include "Core/Camera2D.h"
#include "Utils/include/containers/Vector.h"


int8_t SDLLoader(SDL_Renderer **GfxRenderer, SDL_Window **AppWindow);
void SDLUnloader(SDL_Renderer *GfxRenderer, SDL_Window *AppWindow, SDL_Surface *ImageSurface);
void DrawCharacter(int32_t Event, const float *DeltaTime, Character *BaseCharacter, SDL_Renderer **GfxRenderer,
                   SDL_Texture *Texture);
void DrawObjects(Camera *Camera, SDL_Renderer **GfxRenderer, SDL_Texture **Texture, SDL_Rect *SrcTextureRect,
                 struct Vector *TexturesContainer, int32_t TextureIndex);
void DrawSingleObject(Camera *Camera, SDL_Renderer **GfxRenderer, SDL_Texture *Texture, SDL_Rect *SrcTextureRect);


#endif //SDL_GAME_GAMEENGINECORE_H
