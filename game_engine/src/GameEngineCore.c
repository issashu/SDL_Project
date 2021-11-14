//
// Created by Iordan Tonchev on 8.10.21.
//

#include "utils/defines.h"
#include "Core/GameEngineCore.h"
#include "Core/sdl_methods.h"
#include "Core/Camera2D.h"
#include "Core/sdl_default_app_settings.h"
#include "Managers/WindowManager.h"
#include "Managers/TextureManager.h"
#include "Graphics/GraphicsRenderer2D.h"
#include "Actors/BaseCharacter.h"
#include "utils/Log.h"

//FIXME Replace debug globals with ones from characters/objects/managers
static struct Vector characterTextures;
static struct Vector backgroundTextures;

int8_t SDLLoader(SDL_Renderer **GfxRenderer, SDL_Window **AppWindow) {
       //TODO Take out all error checks in a separate function or move them in a common if
    if (initScreen(AppWindow, WINDOW_WIDTH, WINDOW_HEIGHT) != SUCCESS) {
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

    if (initRenderer(*AppWindow, GfxRenderer) != SUCCESS) {
        LOGERR("initRenderer() failed.");

        return FAILURE;
    }

    return SUCCESS;
}

//FIXME REPLACE THE MAGIC NUMBERS
void DrawCharacter(int32_t Event, const float *DeltaTime, Character *BaseCharacter, SDL_Renderer **GfxRenderer,
                   SDL_Texture *Texture) {

    switch (Event) {
        case SDL_SCANCODE_UP:
            drawAnimation(GfxRenderer, getObjectRect(getBaseObj(BaseCharacter)), Texture, JUMP - 1, JUMP_FRAMES - 1,
                          getAnimationSpeed(BaseCharacter), 96, 84, getHorrizFlip(getBaseObj(BaseCharacter)), *DeltaTime);
            break;

        case SDL_SCANCODE_RIGHT:
            setHorrizFlip(getBaseObj(BaseCharacter), FALSE);
            drawAnimation(GfxRenderer, getObjectRect(getBaseObj(BaseCharacter)), Texture, RUN - 1, RUN_FRAMES - 1,
                          getAnimationSpeed(BaseCharacter), 96, 84, getHorrizFlip(getBaseObj(BaseCharacter)), *DeltaTime);
            break;

        case SDL_SCANCODE_DOWN:

            drawAnimation(GfxRenderer, getObjectRect(getBaseObj(BaseCharacter)), Texture, CROUCH - 1, CROUCH_FRAMES - 1,
                          getAnimationSpeed(BaseCharacter), 96, 84, getHorrizFlip(getBaseObj(BaseCharacter)), *DeltaTime);
            break;

        case SDL_SCANCODE_LEFT:
            setHorrizFlip(getBaseObj(BaseCharacter), TRUE);
            drawAnimation(GfxRenderer, getObjectRect(getBaseObj(BaseCharacter)), Texture, RUN - 1, RUN_FRAMES - 1,
                          getAnimationSpeed(BaseCharacter), 96, 84, getHorrizFlip(getBaseObj(BaseCharacter)), *DeltaTime);
            break;

        case SDL_SCANCODE_SPACE:
            drawAnimation(GfxRenderer, getObjectRect(getBaseObj(BaseCharacter)), Texture, ATTACK - 1, ATTACK_FRAMES - 1,
                          getAnimationSpeed(BaseCharacter), 96, 84, getHorrizFlip(getBaseObj(BaseCharacter)), *DeltaTime);
            break;

        default:
            drawAnimation(GfxRenderer, getObjectRect(getBaseObj(BaseCharacter)), Texture, IDLE - 1, IDLE_FRAMES - 1,
                          getAnimationSpeed(BaseCharacter), 96, 84, getHorrizFlip(getBaseObj(BaseCharacter)), *DeltaTime);
            break;
    }
}

void DrawObjects(Camera *Camera, SDL_Renderer **GfxRenderer, SDL_Texture **Texture, SDL_Rect *SrcTextureRect,
                 struct Vector *TexturesContainer, int32_t TextureIndex) {
    //TODO "Debug if statement": Remove it when passing outside params
    if(TexturesContainer == NONE){
        TexturesContainer = &backgroundTextures;
    }
    destroyTexture(Texture);
    applyTexture(TexturesContainer, Texture, GfxRenderer, TextureIndex);
    drawStatic(GfxRenderer, *Texture, SrcTextureRect, getCameraViewPoint(Camera));
}

void SDLUnloader(SDL_Renderer *GfxRenderer, SDL_Window *AppWindow, SDL_Surface *ImageSurface) {
    //TODO Rethink the whole architecture to have SDL lib unloader and then initializer separately
    //FIXME Pass Image pointer to free
    deinitGame(&AppWindow, &ImageSurface);
    unloadSurfaces(&characterTextures);
    unloadSurfaces(&backgroundTextures);
    destroyRenderer(&GfxRenderer);
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}
