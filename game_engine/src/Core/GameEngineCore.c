//
// Created by Iordan Tonchev on 8.10.21.
//

#include "Utils/include/Defines.h"
#include "Core/GameEngineCore.h"
#include "Core/sdl_methods.h"
#include "Core/Camera2D.h"
#include "Core/sdl_default_app_settings.h"
#include "Managers/WindowManager.h"
#include "Managers/TextureManager.h"
#include "Graphics/GraphicsRenderer2D.h"
#include "Actors/BaseCharacter.h"
#include "Utils/include/Log.h"


int8_t SDLLoader(SDL_Renderer **GfxRenderer, SDL_Window **AppWindow) {

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

void DrawCharacter(int32_t Event, const float *DeltaTime, Character *BaseCharacter, SDL_Renderer **GfxRenderer,
                   SDL_Texture *Texture) {

    switch (Event) {
        case SDL_SCANCODE_UP:
            drawAnimation(GfxRenderer, getObjectRect(getBaseObj(BaseCharacter)), Texture, JUMP - 1, JUMP_FRAMES - 1,
                          getAnimationSpeed(BaseCharacter), getObjectRect(getBaseObj(BaseCharacter))->w,
                          getObjectRect(getBaseObj(BaseCharacter))->h,
                          getHorrizFlip(getBaseObj(BaseCharacter)), *DeltaTime);
            break;

        case SDL_SCANCODE_RIGHT:
            setHorrizFlip(getBaseObj(BaseCharacter), FALSE);
            drawAnimation(GfxRenderer, getObjectRect(getBaseObj(BaseCharacter)), Texture, RUN - 1, RUN_FRAMES - 1,
                          getAnimationSpeed(BaseCharacter), getObjectRect(getBaseObj(BaseCharacter))->w,
                          getObjectRect(getBaseObj(BaseCharacter))->h,
                          getHorrizFlip(getBaseObj(BaseCharacter)), *DeltaTime);
            break;

        case SDL_SCANCODE_DOWN:

            drawAnimation(GfxRenderer, getObjectRect(getBaseObj(BaseCharacter)), Texture, CROUCH - 1, CROUCH_FRAMES - 1,
                          getAnimationSpeed(BaseCharacter), getObjectRect(getBaseObj(BaseCharacter))->w,
                          getObjectRect(getBaseObj(BaseCharacter))->h,
                          getHorrizFlip(getBaseObj(BaseCharacter)), *DeltaTime);
            break;

        case SDL_SCANCODE_LEFT:
            setHorrizFlip(getBaseObj(BaseCharacter), TRUE);
            drawAnimation(GfxRenderer, getObjectRect(getBaseObj(BaseCharacter)), Texture, RUN - 1, RUN_FRAMES - 1,
                          getAnimationSpeed(BaseCharacter), getObjectRect(getBaseObj(BaseCharacter))->w,
                          getObjectRect(getBaseObj(BaseCharacter))->h,
                          getHorrizFlip(getBaseObj(BaseCharacter)), *DeltaTime);
            break;

        case SDL_SCANCODE_SPACE:
            drawAnimation(GfxRenderer, getObjectRect(getBaseObj(BaseCharacter)), Texture, ATTACK - 1, ATTACK_FRAMES - 1,
                          getAnimationSpeed(BaseCharacter), getObjectRect(getBaseObj(BaseCharacter))->w,
                          getObjectRect(getBaseObj(BaseCharacter))->h,
                          getHorrizFlip(getBaseObj(BaseCharacter)), *DeltaTime);
            break;

        case DEAD:
            drawAnimation(GfxRenderer,getObjectRect(getBaseObj(BaseCharacter)),Texture, DIE - 1, DIE_FRAMES - 1,
                          getAnimationSpeed(BaseCharacter), getObjectRect(getBaseObj(BaseCharacter))->w,
                          getObjectRect(getBaseObj(BaseCharacter))->h,
                          getHorrizFlip(getBaseObj(BaseCharacter)), *DeltaTime);
            break;

        default:
            drawAnimation(GfxRenderer, getObjectRect(getBaseObj(BaseCharacter)), Texture, IDLE - 1, IDLE_FRAMES - 1,
                          getAnimationSpeed(BaseCharacter), getObjectRect(getBaseObj(BaseCharacter))->w,
                          getObjectRect(getBaseObj(BaseCharacter))->h,
                          getHorrizFlip(getBaseObj(BaseCharacter)), *DeltaTime);
            break;
    }
}

void DrawObjects(Camera *Camera, SDL_Renderer **GfxRenderer, SDL_Texture **Texture, SDL_Rect *SrcTextureRect,
                 struct Vector *TexturesContainer, int32_t TextureIndex) {
    destroyTexture(Texture);
    applyTexture(TexturesContainer, Texture, GfxRenderer, TextureIndex);
    drawStatic(GfxRenderer, *Texture, SrcTextureRect, getCameraViewPoint(Camera));
}

void DrawSingleObject(GameObject2D *object, SDL_Renderer **GfxRenderer, SDL_Texture *Texture, SDL_Rect *SrcTextureRect) {
    drawStatic(GfxRenderer, Texture, SrcTextureRect, getObjectRect(object));
}

void SDLUnloader(SDL_Renderer *GfxRenderer, SDL_Window *AppWindow, SDL_Surface *ImageSurface) {
    //TODO Rethink the whole architecture to have SDL lib unloader and then initializer separately
    //FIXME Pass Image pointer to free
    deinitGame(&AppWindow, &ImageSurface);
    destroyRenderer(&GfxRenderer);
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}
