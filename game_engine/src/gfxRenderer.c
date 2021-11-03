//
// Created by Iordan Tonchev on 10.10.21.
//

#include "Graphics/gfxRenderer.h"
#include "Managers/TextureManager.h"

#define STORAGE_START_CAPACITY 1

//For testing purposes, remove the global vector here after debugging
//struct Vector testTextures2;

//FIXME REMOVE MAGIC NUMBERS
BOOL loadSurfaces(struct Vector *objTextures) {
    initTextureStorage(objTextures, STORAGE_START_CAPACITY);
    //TODO Learn to use glob to load any number of textures into a vector
    loadTextures(objTextures, (ASSETS_PATH "images/character_anim.png"));
    for (int8_t i = 0; i < 1; i++) {
        if (getElementVector(objTextures, i) == NULL) {
            LOGERR("SDL_LoadIMG failed! Reason: %s", SDL_GetError());
            return FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

BOOL initRenderer(SDL_Window *Window, SDL_Renderer **Renderer) {
    *Renderer = SDL_CreateRenderer(Window, -1, (SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED));
    if (*Renderer == NULL) {
        LOGERR("SDL_renderer could not be initialised! Reason: %s", SDL_GetError());
        return FAILURE;
    }
    return EXIT_SUCCESS;
}

void drawStatic(SDL_Renderer **Renderer, SDL_Texture *Texture) {
    SDL_RenderCopy(*Renderer, Texture, NULL, NULL);
    SDL_RenderPresent(*Renderer);
}

void drawAnimation(SDL_Renderer **Renderer, SDL_Texture *Texture, int32_t animType, int32_t firstFrame,
                   float animSpeed, int transX, int transY, int Width, int Height, BOOL hFlip) {

    //This will always keep rotating up to the maximum available sprites in the animation, since % will revert to 0
    int32_t currentFrame = (int32_t )(SDL_GetTicks() / animSpeed) % firstFrame;
    SDL_Rect srcFrame = {.x=Width * currentFrame, .y=Height * animType, .w = Width, .h = Height};
    SDL_Rect dstFrame = {.x=transX, .y=transY, .w = Width, .h = Height};

    SDL_RenderClear(*Renderer);
    SDL_RenderCopyEx(*Renderer, Texture, &srcFrame, &dstFrame, 0, NULL, hFlip);
    SDL_RenderPresent(*Renderer);
}







