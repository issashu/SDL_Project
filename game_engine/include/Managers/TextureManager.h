//
// Created by Iordan Tonchev on 23.10.21.
//

#ifndef SDL_GAME_TEXTUREMANAGER_H
#define SDL_GAME_TEXTUREMANAGER_H

#include "utils/defines.h"
#include "utils/containers/Vector.h"

//TODO Apply singleton by:
// 1. Make the manager into struct.
// 2. Initialise as external global.
// 3. In the init method put an if with isCreated flag.
// 4. Raise flag on init, put down on deinit.
// 5. If the flag is down, create new instance (initialise). If it is up - return pointer to the existing one ^^

void initTextureStorage(struct Vector *textureMap, size_t initialCapacity);
BOOL loadTextures(struct Vector *textureMap, char *texturePath);
BOOL destroyTexture(SDL_Texture **texture);
BOOL applyTexture(struct Vector *textureMap, SDL_Texture **Texture, SDL_Renderer **Renderer, size_t index);
void unloadTextures(struct Vector *textures);

#endif //SDL_GAME_TEXTUREMANAGER_H
