//
// Created by Iordan Tonchev on 23.10.21.
//

#ifndef SDL_GAME_TEXTUREMANAGER_H
#define SDL_GAME_TEXTUREMANAGER_H

#include "utils/defines.h"
#include "utils/containers/Vector.h"

//TODO Apply singleton

void initTextureStorage(struct Vector *textures, size_t initialCapacity);
BOOL loadTexture(STRING texturePath, struct Vector *textures);
BOOL applyTexture(SDL_Surface *Image, SDL_Texture **Texture, SDL_Renderer *Renderer);
void unloadTexture(struct Vector *textures);
void freeTexture(struct Vector *textures);

#endif //SDL_GAME_TEXTUREMANAGER_H
