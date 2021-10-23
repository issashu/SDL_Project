//
// Created by Iordan Tonchev on 23.10.21.
//

#include <stdint.h>
#include <SDL_image.h>

#include "Managers/TextureManager.h"

void initTextureStorage(struct Vector *textures, size_t initialCapacity) {
    textures = malloc(sizeof(struct Vector)*initialCapacity);
    initVector(textures, initialCapacity);
}

BOOL loadTexture(STRING texturePath, struct Vector *textures){
    pushElementVector(textures, IMG_Load(texturePath));

    return SUCCESS;
}

BOOL applyTexture(SDL_Surface *Image, SDL_Texture **Texture, SDL_Renderer *Renderer){
    *Texture = SDL_CreateTextureFromSurface(Renderer, Image);

    if (*Texture == NULL) {
        printf("Failed to load texture from asset! Reason: %s\n", SDL_GetError());
        return FAILURE;
    }
    return SUCCESS;
}

void UNUSED unloadTexture(struct Vector *textures) {
   UNUSED size_t texturesCount = getSizeVector(textures);
}

void freeTexture(struct Vector *textures) {
    freeVector(textures);
}