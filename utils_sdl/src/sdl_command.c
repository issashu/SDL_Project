//
// Created by Iordan Tonchev on 8.10.21.
//

#include "defines.h"
#include "sdl_command.h"
#include "sdl_methods.h"
#include "sdl_gfx_renderer.h"
#include "Log.h"

//TODO Check how to utilise the forward declared struct and function pointers
struct SDLMethods{
    int32_t (*loadResources)(SDL_Surface**, const STRING);
    void (*drawGraphics)(SDL_Window**, SDL_Surface**, SDL_Surface**);
    void (*deinitGame)(SDL_Window**, SDL_Surface**);
};

//TODO Make non-global and after fix the drawGame spaghetti below
static struct SDLWindow AppWindow;
SDL_Surface ImageSurfaces [KEY_PRESS_SURFACE_TOTAL];

int8_t SDLLoader(){
    //TODO Rethink the whole arhitecture to have SDL lib loader and then initialiser separetly
    AppWindow.Window =NULL;
    AppWindow.ScreenSurface = NULL;
    AppWindow.Image = NULL;

 //TODO Add some use of the gameEvent pointer or delete
 //SDL_Event *gameEvent = NULL;
    //TODO Fix the path abomination by possibly using path as param.
    const STRING ImagePath = ASSETS_PATH "images/hello.bmp";

    //TODO Take out all error checks in a separate function or move them in a common if
    if (initScreen(&AppWindow.Window, &AppWindow.ScreenSurface) != SUCCESS) {
        LOGERR("initScreen() failed.");
        //TODO Add info for file, line and path
        return FAILURE;
    }

    if (initText() != SUCCESS) {
        LOGERR("initText() failed.");
        //TODO Add info  for file, line and path
        return FAILURE;
    }

    if (initTextures() != SUCCESS) {
        LOGERR("initTextures() failed.");
        //TODO Add info  for file, line and path
        return FAILURE;
    }

    if (initTimers() != SUCCESS) {
        LOGERR("initTimers() failed.");
        //TODO Add info  for file, line and path
        return FAILURE;
    }

    if (initSFX() != SUCCESS) {
        LOGERR("initSFX() failed.");
        //TODO Add info  for file, line and path
        return FAILURE;
    }

    if (loadResources(&AppWindow.Image, &ImagePath) != SUCCESS) {
        LOGERR("loadResources() failed.");
        //TODO Add info  for file, line and path
        return FAILURE;
    }

    return SUCCESS;
}

void SDLdrawGame(){
    drawGraphics(&AppWindow.Window,&AppWindow.ScreenSurface,&AppWindow.Image);
}

void SDLUnloader(){
    //TODO Rethink the whole arhitecture to have SDL lib unloader and then initialiser separetly
    deinitGame(&AppWindow.Window, &AppWindow.Image);
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}
