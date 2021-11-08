//
// Created by Iordan Tonchev on 23.10.21.
//

#include <stdint.h>
#include <SDL_image.h>

#include "Managers/TextureManager.h"
//TODO Add error messages and checking
void initTextureStorage(struct Vector *textureMap, size_t initialCapacity) {
    textureMap = malloc(sizeof(struct Vector) * initialCapacity);
    initVector(textureMap, initialCapacity);
}

BOOL loadTextures(struct Vector *textureMap, char *texturePath) {
    pushElementVector(textureMap, IMG_Load(texturePath));

    return SUCCESS;
}

BOOL applyTexture(struct Vector *textureMap, SDL_Texture **Texture, SDL_Renderer *Renderer, size_t index) {
    SDL_Surface *Image = (SDL_Surface*)getElementVector(textureMap, index);
    *Texture = SDL_CreateTextureFromSurface(Renderer, Image);

    if (*Texture == NULL) {
        printf("Failed to load texture from asset! Reason: %s\n", SDL_GetError());
        return FAILURE;
    }

    return SUCCESS;
}

BOOL destroyTexture(SDL_Texture *texture){
    if (texture == NULL) {
        printf("Failed to free Texture memory! Reason: %s\n", SDL_GetError());
        return FAILURE;
    }

    SDL_DestroyTexture(texture);

    return SUCCESS;
}


//TODO Use on destroy object.
void unloadTexture(struct Vector *textures) {
    if (textures!= NULL){
        size_t texturesCount = getSizeVector(textures);
        for (size_t i = 0; i<texturesCount; i++){
            if(textures->items[i]!=NULL){
                free(textures->items[i]);
                textures->items[i] = NULL;
            }
        }
        freeVector(textures);
        textures = NULL;
    }
}