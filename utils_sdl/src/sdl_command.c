//
// Created by Iordan Tonchev on 8.10.21.
//

#include "defines.h"
#include "sdl_command.h"
#include "sdl_methods.h"
#include "Log.h"

//TODO Check how to utilise the forward derclared struct and function pointers
struct SDLMethods{
    int32_t (*loadResources)(SDL_Surface**, const STRING);
    void (*drawGraphics)(SDL_Window**, SDL_Surface**, SDL_Surface**);
    void (*deinitGame)(SDL_Window**, SDL_Surface**);
};

int8_t SDLLoader(){
    //TODO Rethink the whole arhitecture to have SDL lib loader and then initialiser separetly
    SDL_Window *Window = NULL;
    SDL_Surface *screenSurface = NULL;
    SDL_Surface *Image = NULL;
    SDL_Event *gameEvent = NULL;

    //TODO Take out all error checks in a separate function ot move that in the init
    if (initScreen(&Window, &screenSurface) != SUCCESS) {
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

    return SUCCESS;
}

void SDLUnloader(){
    //TODO Rethink the whole arhitecture to have SDL lib unloader and then initialiser separetly
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}
