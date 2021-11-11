//
// Created by Iordan Tonchev on 23.10.21.
//

#ifndef SDL_GAME_TEXTUREMANAGER_H
#define SDL_GAME_TEXTUREMANAGER_H

#include "utils/defines.h"
#include "utils/containers/Vector.h"

//TODO Apply singleton

void initTextureStorage(struct Vector *textureMap, size_t initialCapacity);
BOOL loadTextures(struct Vector *textureMap, char *texturePath);
BOOL destroyTexture(SDL_Texture **texture);
BOOL applyTexture(struct Vector *textureMap, SDL_Texture **Texture, SDL_Renderer **Renderer, size_t index);
void unloadTextures(struct Vector *textures);

#endif //SDL_GAME_TEXTUREMANAGER_H
