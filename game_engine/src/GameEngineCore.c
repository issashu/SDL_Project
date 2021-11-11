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
#include "Actors/PlayerCharacter.h"
#include "utils/Log.h"

//FIXME Replace debug globals with ones from characters/objects/managers
static struct Vector characterTextures;
static struct Vector backgroundTextures;
static SDL_Window *AppWindow;
static SDL_Renderer *GfxRenderer = NULL;

int8_t SDLLoader(playerActor *Player) {
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

    if (loadSurfaces(&characterTextures, getSpriteSheet(getBaseChar(Player))) != SUCCESS) {
        LOGERR("loadSurfaces() failed.");

        return FAILURE;
    }

    /*
     pushElementVector(textureMap, IMG_Load(ASSETS_PATH "images/Enemies/enemy_sheet_black.png"));
     pushElementVector(textureMap, IMG_Load(ASSETS_PATH "images/Enemies/enemy_sheet_blue.png"));
     pushElementVector(textureMap, IMG_Load(ASSETS_PATH "images/Enemies/enemy_sheet_green.png"));
     pushElementVector(textureMap, IMG_Load(ASSETS_PATH "images/Enemies/enemy_sheet_red.png"));
     pushElementVector(textureMap, IMG_Load(ASSETS_PATH "images/Enemies/enemy_sheet_yellow.png"));

     ASSETS_PATH "images/Background/Layer_0.png"
     ASSETS_PATH "images/Background/Layer_1.png"
     ASSETS_PATH "images/Background/Layer_2.png"
     ASSETS_PATH "images/Background/Layer_3.png"
     ASSETS_PATH "images/Background/Layer_4.png"
     ASSETS_PATH "images/Background/Layer_5.png"
     ASSETS_PATH "images/Background/Layer_6.png"
     ASSETS_PATH "images/Background/Layer_7.png"
     ASSETS_PATH "images/Background/Layer_8.png"
     ASSETS_PATH "images/Background/Layer_9.png"
     ASSETS_PATH "images/Background/Layer_10.png"
     ASSETS_PATH "images/Background/Layer_11.png"
     */

    if (loadSurfaces(&characterTextures, ASSETS_PATH "images/Enemies/enemy_sheet_red.png") != SUCCESS) {
        LOGERR("loadSurfaces() failed.");

        return FAILURE;
    }

    if (loadSurfaces(&backgroundTextures, ASSETS_PATH "images/Background/Layer_0.png") != SUCCESS) {
        LOGERR("loadSurfaces() failed.");

        return FAILURE;
    }

    if (loadSurfaces(&backgroundTextures, ASSETS_PATH "images/Background/Layer_1.png") != SUCCESS) {
        LOGERR("loadSurfaces() failed.");

        return FAILURE;
    }

    if (loadSurfaces(&backgroundTextures, ASSETS_PATH "images/Background/Layer_2.png") != SUCCESS) {
        LOGERR("loadSurfaces() failed.");

        return FAILURE;
    }

    if (loadSurfaces(&backgroundTextures, ASSETS_PATH "images/Background/Layer_3.png") != SUCCESS) {
        LOGERR("loadSurfaces() failed.");

        return FAILURE;
    }

    if (loadSurfaces(&backgroundTextures, ASSETS_PATH "images/Background/Layer_4.png") != SUCCESS) {
        LOGERR("loadSurfaces() failed.");

        return FAILURE;
    }

    if (loadSurfaces(&backgroundTextures, ASSETS_PATH "images/Background/Layer_5.png") != SUCCESS) {
        LOGERR("loadSurfaces() failed.");

        return FAILURE;
    }

    if (loadSurfaces(&backgroundTextures, ASSETS_PATH "images/Background/Layer_6.png") != SUCCESS) {
        LOGERR("loadSurfaces() failed.");

        return FAILURE;
    }

    if (loadSurfaces(&backgroundTextures, ASSETS_PATH "images/Background/Layer_7.png") != SUCCESS) {
        LOGERR("loadSurfaces() failed.");

        return FAILURE;
    }

    if (loadSurfaces(&backgroundTextures, ASSETS_PATH "images/Background/Layer_8.png") != SUCCESS) {
        LOGERR("loadSurfaces() failed.");

        return FAILURE;
    }

    if (loadSurfaces(&backgroundTextures, ASSETS_PATH "images/Background/Layer_9.png") != SUCCESS) {
        LOGERR("loadSurfaces() failed.");

        return FAILURE;
    }

    if (loadSurfaces(&backgroundTextures, ASSETS_PATH "images/Background/Layer_10.png") != SUCCESS) {
        LOGERR("loadSurfaces() failed.");

        return FAILURE;
    }

    if (loadSurfaces(&backgroundTextures, ASSETS_PATH "images/Background/Layer_11.png") != SUCCESS) {
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
//TODO Unite DrawCharacter and DrawCamera in one method to have single Render clear and prtesent
void DrawCharacter(int32_t Event, float *DeltaTime, Character *BaseCharacter) {
    SDL_Texture *Texture = NULL;
    clearRenderer(&GfxRenderer);
    if (Event==0){
        applyTexture(&characterTextures, &Texture, GfxRenderer, 0);
        drawAnimation(&GfxRenderer, getObjRect(getBaseObj(BaseCharacter)), Texture, IDLE - 1, IDLE_FRAMES - 1,
                      getAnimationSpeed(BaseCharacter), 96, 84, FALSE, *DeltaTime);
        destroyTexture(&Texture);
    }
    else {
        applyTexture(&characterTextures, &Texture, GfxRenderer, 0);
        switch (Event) {
            case SDL_SCANCODE_UP:
                drawAnimation(&GfxRenderer, getObjRect(getBaseObj(BaseCharacter)), Texture, JUMP - 1, JUMP_FRAMES - 1,
                              getAnimationSpeed(BaseCharacter), 96, 84, FALSE, *DeltaTime);
                break;

            case SDL_SCANCODE_RIGHT:
                drawAnimation(&GfxRenderer, getObjRect(getBaseObj(BaseCharacter)), Texture, RUN - 1, RUN_FRAMES - 1,
                              getAnimationSpeed(BaseCharacter), 96, 84, FALSE, *DeltaTime);
                break;

            case SDL_SCANCODE_DOWN:
                drawAnimation(&GfxRenderer, getObjRect(getBaseObj(BaseCharacter)), Texture, CRAWL - 1, CRAWL_FRAMES - 1,
                              getAnimationSpeed(BaseCharacter), 96, 84, FALSE, *DeltaTime);
                break;

            case SDL_SCANCODE_LEFT:
                drawAnimation(&GfxRenderer, getObjRect(getBaseObj(BaseCharacter)), Texture, RUN - 1, RUN_FRAMES - 1,
                              getAnimationSpeed(BaseCharacter), 96, 84, TRUE, *DeltaTime);
                break;

            default:
                drawAnimation(&GfxRenderer, getObjRect(getBaseObj(BaseCharacter)), Texture, IDLE - 1, IDLE_FRAMES - 1,
                              getAnimationSpeed(BaseCharacter), 96, 84, FALSE, *DeltaTime);
                break;
        }
    }
    presentRenderer(GfxRenderer);
    destroyTexture(&Texture);
}

void DrawCamera(Camera *Camera){
    static SDL_Texture *Texture = NULL;
    clearRenderer(&GfxRenderer);
    applyTexture(&backgroundTextures, &Texture, GfxRenderer, 0);
    drawStatic(&GfxRenderer, Texture, NULL, getCameraViewPoint(Camera));
    presentRenderer(GfxRenderer);
    destroyTexture(&Texture);
}


void SDLUnloader() {
    //TODO Rethink the whole architecture to have SDL lib unloader and then initializer separately
    //FIXME Pass Image pointer to free
    deinitGame(&AppWindow, NULL);
    unloadSurfaces(&characterTextures);
    unloadSurfaces(&backgroundTextures);
    destroyRenderer(&GfxRenderer);
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}
