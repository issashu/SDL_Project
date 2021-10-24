//
// Created by Iordan Tonchev on 10.10.21.
//

#include "Graphics/sdl_gfx_renderer.h"
#include "Managers/TextureManager.h"

//For testing purposes, remove the global vector here after debugging
//struct Vector testTextures2;


BOOL loadSurfaces(struct Vector *objTextures) {
    initTextureStorage(objTextures, KEY_PRESS_SURFACE_TOTAL);
    //TODO Learn to use glob to load any number of textures into a vector
    loadTextures(objTextures, (ASSETS_PATH "images/hello.png"));
    loadTextures(objTextures, (ASSETS_PATH "images/down.png"));
    loadTextures(objTextures, (ASSETS_PATH "images/up.png"));
    loadTextures(objTextures, (ASSETS_PATH "images/left.png"));
    loadTextures(objTextures, (ASSETS_PATH "images/right.png"));
    for (int8_t i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
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

void animateSprites(){

}







