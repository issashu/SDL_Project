//
// Created by Iordan Tonchev on 10.10.21.
//

#include "sdl_gfx_renderer.h"
#include "Log.h"

BOOL loadSurfaces(SDL_Surface *Images) {
    //TODO Learn to use glob to load any number of textures into a vector
    //const STRING ImgPath = ASSETS_PATH "images/hello.png";
    Images[KEY_PRESS_SURFACE_DEFAULT] = *IMG_Load(ASSETS_PATH "images/hello.png");
    Images[KEY_PRESS_SURFACE_DOWN] = *IMG_Load(ASSETS_PATH "images/down.png");
    Images[KEY_PRESS_SURFACE_UP] = *IMG_Load(ASSETS_PATH "images/up.png");
    Images[KEY_PRESS_SURFACE_LEFT] = *IMG_Load(ASSETS_PATH "images/left.png");
    Images[KEY_PRESS_SURFACE_RIGHT] = *IMG_Load(ASSETS_PATH "images/right.png");

    for (int8_t i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
        if (Images + i == NULL) {
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

BOOL setTexture(SDL_Surface *Image, SDL_Texture **Texture, SDL_Renderer *Renderer) {
    *Texture = SDL_CreateTextureFromSurface(Renderer, Image);

    if (*Texture == NULL) {
        printf("Failed to load texture from asset! Reason: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}







