//
// Created by Iordan Tonchev on 8.10.21.
//

#include "utils/defines.h"
#include "Core/GameEngineCore.h"
#include "Core/sdl_methods.h"
#include "Core/sdl_default_app_settings.h"
#include "Managers/WindowManager.h"
#include "Managers/TextureManager.h"
#include "Graphics/GraphicsRenderer2D.h"
#include "Actors/BaseCharacter.h"
#include "utils/Log.h"

//FIXME Replace debug globals with ones from characters/objects/managers
static struct Vector testTextures;
static SDL_Window *AppWindow;
static SDL_Texture *Texture = NULL;
static SDL_Renderer *GfxRenderer = NULL;
static float AnimationSpeed = 150.0f;

int8_t SDLLoader() {
    //TODO Rethink the whole architecture to have SDL lib loader and then initializer separately
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

    if (loadSurfaces(&testTextures) != SUCCESS) {
        LOGERR("loadSurfaces() failed.");

        return FAILURE;
    }

    if (initRenderer(AppWindow, &GfxRenderer) != SUCCESS) {
        LOGERR("initRenderer() failed.");

        return FAILURE;
    }

    return SUCCESS;
}

//FIXME REPLACE THE MAGIC NUMBERS and move delta time into a timer manager
void DrawGame(int32_t Event, float DeltaTime) {
    applyTexture(&testTextures, &Texture, GfxRenderer, 0);
    switch (Event) {
        case SDL_SCANCODE_UP:
            drawAnimation(&GfxRenderer, Texture, JUMP - 1, JUMP_FRAMES - 1, AnimationSpeed,
                          200, 200, 96, 84, FALSE, DeltaTime);
            break;

        case SDL_SCANCODE_RIGHT:
            drawAnimation(&GfxRenderer, Texture, RUN - 1, RUN_FRAMES - 1, AnimationSpeed,
                          200, 200, 96, 84, FALSE, DeltaTime);
            break;

        case SDL_SCANCODE_DOWN:
            drawAnimation(&GfxRenderer, Texture, CRAWL - 1, CRAWL_FRAMES - 1, AnimationSpeed,
                          200, 200, 96, 84, FALSE, DeltaTime);
            break;

        case SDL_SCANCODE_LEFT:
            drawAnimation(&GfxRenderer, Texture, RUN - 1, RUN_FRAMES - 1, AnimationSpeed,
                          200, 200, 96, 84, TRUE, DeltaTime);
            break;

        default:
            drawAnimation(&GfxRenderer, Texture, IDLE - 1, IDLE_FRAMES - 1, AnimationSpeed,
                          200, 200, 96, 84, FALSE, DeltaTime);
            break;
    }
}

void SDLUnloader() {
    //TODO Rethink the whole architecture to have SDL lib unloader and then initializer separately
    //FIXME Pass Image pointer to free
    deinitGame(&AppWindow, NULL);
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}
