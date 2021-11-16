//
// Created by Iordan Tonchev on 10.10.21.
//

#include "Graphics/GraphicsRenderer2D.h"
#include "Managers/TextureManager.h"

#define STORAGE_START_CAPACITY 1

// (ASSETS_PATH "images/character_anim1.png")

BOOL initRenderer(SDL_Window *Window, SDL_Renderer **Renderer) {
    *Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (*Renderer == NULL) {
        LOGERR("SDL_renderer could not be initialised! Reason: %s", SDL_GetError());
        return FAILURE;
    }
    SDL_SetRenderDrawColor(*Renderer,0,0,0,1);
    return EXIT_SUCCESS;
}

//FIXME REMOVE MAGIC NUMBERS
BOOL loadSurfaces(struct Vector *objTextures, STRING TexturePath) {
    if (objTextures == NONE){
        initTextureStorage(objTextures, STORAGE_START_CAPACITY);
    }
    //TODO Learn to use glob to load any number of textures into a vector
    loadImageSurfaces(objTextures, TexturePath);
    for (int8_t i = 0; i < 1; i++) {
        if (getElementVector(objTextures, i) == NULL) {
            LOGERR("SDL_LoadIMG failed! Reason: %s", SDL_GetError());
            return FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

void unloadSurfaces(struct Vector *objTextures) {
    if (objTextures != NONE){
        unloadTextures(objTextures);
    }
}

void drawStatic(SDL_Renderer **Renderer, SDL_Texture *Texture, SDL_Rect *SrcRect, SDL_Rect *DstRect) {
    SDL_RenderCopy(*Renderer, Texture, SrcRect, DstRect);
}

void drawAnimation(SDL_Renderer **Renderer, const SDL_Rect *targetFrame, SDL_Texture *Texture, int32_t animType,
                   int32_t firstFrame, float animSpeed, int Width, int Height, BOOL hFlip, float UNUSED DeltaTime) {

    //This will always keep rotating up to the maximum available sprites in the animation, then reset,
    // since % will revert to 0 eventually
    int32_t currentFrame = ((int32_t )((SDL_GetTicks() / animSpeed)) % firstFrame);
    SDL_Rect srcFrame = {.x=Width * currentFrame, .y=Height * animType, .w = Width, .h = Height};
    SDL_Rect dstFrame = *targetFrame;
    SDL_RenderCopyEx(*Renderer, Texture, &srcFrame, &dstFrame, 0, NULL, hFlip);
    if(currentFrame != 0){
        currentFrame = 0;
    }
}

void clearRenderer(SDL_Renderer **Renderer) {
    SDL_RenderClear(*Renderer);
}

void presentRenderer(SDL_Renderer *Renderer){
    SDL_RenderPresent(Renderer);
}

void destroyRenderer(SDL_Renderer **Renderer){
    SDL_DestroyRenderer(*Renderer);
    *Renderer = NULL;
}







