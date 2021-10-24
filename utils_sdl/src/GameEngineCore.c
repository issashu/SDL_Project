//
// Created by Iordan Tonchev on 8.10.21.
//

#include "utils/defines.h"
#include "Core/GameEngineCore.h"
#include "Core/sdl_methods.h"
#include "Core/sdl_default_app_settings.h"
#include "Managers/WindowManager.h"
#include "Managers/TextureManager.h"
#include "Graphics/gfxRenderer.h"
#include "utils/Log.h"

//TODO Make non-global and after fix the drawGame spaghetti below
static SDL_Window *AppWindow;

SDL_Surface ImageSurfaces [KEY_PRESS_SURFACE_TOTAL];
static struct Vector testTextures;
static SDL_Texture *Texture = NULL;
static SDL_Renderer *GfxRenderer = NULL;

int8_t SDLLoader(){
    //TODO Rethink the whole arhitecture to have SDL lib loader and then initialiser separetly
   AppWindow = NULL;

    //TODO Take out all error checks in a separate function or move them in a common if
    if (initScreen(&AppWindow, WINDOW_WIDTH, WINDOW_HEIGHT) != SUCCESS) {
        LOGERR("initScreen() failed.");

        return FAILURE;
    }

    if (initText() != SUCCESS) {
        LOGERR("initText() failed.");

        return FAILURE;
    }

    if (initTextures() != SUCCESS) {
        LOGERR("initTextures() failed.");

        return FAILURE;
    }

    if (initTimers() != SUCCESS) {
        LOGERR("initTimers() failed.");

        return FAILURE;
    }

    if (initSFX() != SUCCESS) {
        LOGERR("initSFX() failed.");

        return FAILURE;
    }

    if(loadSurfaces(&testTextures) != SUCCESS){
        LOGERR("loadSurfaces() failed.");

        return FAILURE;
    }

    //FIXME Need to use a variable instead of the getter
    if(initRenderer(AppWindow, &GfxRenderer) != SUCCESS) {
        LOGERR("initRenderer() failed.");

        return FAILURE;
    }

    return SUCCESS;
}

void SDLdrawGame(int32_t TextureIndex) {
    applyTexture(&testTextures, &Texture, GfxRenderer, TextureIndex);
    drawGraphics(&GfxRenderer, Texture);
}

void SDLUnloader(){
    //TODO Rethink the whole arhitecture to have SDL lib unloader and then initialiser separetly
    deinitGame(&AppWindow, NULL);
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}
