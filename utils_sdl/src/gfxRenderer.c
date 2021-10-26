//
// Created by Iordan Tonchev on 10.10.21.
//

#include "Graphics/gfxRenderer.h"
#include "Managers/TextureManager.h"

//For testing purposes, remove the global vector here after debugging
//struct Vector testTextures2;

//FIXME REMOVE MAGIC NUMBERS
BOOL loadSurfaces(struct Vector *objTextures) {
    initTextureStorage(objTextures, 1);
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
    *Renderer = SDL_CreateRenderer(Window, -1, 0);
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

void
drawAnimation(SDL_Renderer **Renderer, SDL_Texture *Texture, int32_t animType, int32_t firstFrame, int32_t animSpeed,
              int transX, int transY, int Width, int Height, BOOL vFlip, BOOL hFlip) {

    int32_t currentFrame = (SDL_GetTicks() / animSpeed) % firstFrame;
    SDL_Rect srcFrame = {.x=Width * currentFrame, .y=Height * animType, .w = Width, .h = Height};
    SDL_Rect dstFrame = {.x=transX, .y=transY, .w = Width, .h = Height};

    //Remove. for debugging only or add vertical flip ideas
    vFlip = FALSE;
    SDL_RenderCopyEx(*Renderer, Texture, &srcFrame, &dstFrame, 0, NULL, hFlip);
    SDL_RenderPresent(*Renderer);
}







