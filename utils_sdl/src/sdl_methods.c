//
// Created by Iordan Tonchev on 6.10.21.
//


#include "sdl_methods.h"
#include "defines.h"
#include "Log.h"

int32_t initScreen(SDL_Window **Window, SDL_Surface **WindowSurface) {
    if (SDL_Init(SDL_INIT_VIDEO) != SUCCESS) {
        LOGERR("SDL_Init_VIDEO() failed! Reason: %s", SDL_GetError());
        //TODO Add filename, path and line number to the logger
        //TODO Why do we use a macro in LOGGER?
        return FAILURE;
    }
    //TODO REMOVE THE MAGIC NUMBERS AS PARAMS
    *Window = SDL_CreateWindow("Metroidvania", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, \
                                640, 860, SDL_WINDOW_SHOWN);
    if (*Window == NULL) {
        LOGERR("SDL_CreateWindow failed! Reason: %s", SDL_GetError());
        //TODO Add filename, path and line number to the logger
        return FAILURE;
    }

    *WindowSurface = SDL_GetWindowSurface(*Window);
    if (*WindowSurface == NULL) {
        LOGERR("SDL_GetWindowSurface has failed! Reason: %s", SDL_GetError());
        //TODO Add filename, path and line number to the logger
        return FAILURE;
    }

    return EXIT_SUCCESS;
}

int32_t initText(){
    if (TTF_Init() != SUCCESS) {
        LOGERR("TTF_Init() failed! Reason: %s", SDL_GetError());
        //TODO Add filename, path and line number to the logger
        //TODO Why do we use a macro in LOGGER?
        return FAILURE;
    }
}

int32_t initTextures(){
    const int32_t imgFlags = IMG_INIT_PNG;

    if (! (IMG_Init(imgFlags) & imgFlags)) {
        LOGERR("SDL_image could not be initialised! SDL_image Error: %s",
               IMG_GetError());
        return FAILURE;
    }
}

int32_t initTimers(){
    if (SDL_Init(SDL_INIT_TIMER) != SUCCESS) {
        LOGERR("SDL_Init_TIMER() failed! Reason: %s", SDL_GetError());
        //TODO Add filename, path and line number to the logger
        //TODO Why do we use a macro in LOGGER?
        return FAILURE;
    }
}

int32_t initSFX() {
    if (SDL_Init(SDL_INIT_AUDIO) != SUCCESS) {
        LOGERR("SDL_Init_AUDIO() failed! Reason: %s", SDL_GetError());
        //TODO Add filename, path and line number to the logger
        //TODO Why do we use a macro in LOGGER?
        return FAILURE;
    }

    if (0 > Mix_OpenAudio(44100,      //sound frequency
                          MIX_DEFAULT_FORMAT,  //sample format
                          2,          //stereo hardware channels
                          2048)) {   //chunk size
        LOGERR("SDL_mixer could not be initialised! SDL Error: %s", Mix_GetError());
        return FAILURE;
    }

}

int32_t loadResources(SDL_Surface **Image, const STRING*ImagePath) {
    *Image = SDL_LoadBMP(*ImagePath);
    if (*Image == NULL) {
        LOGERR("SDL_LoadBMP failed! Reason: %s", SDL_GetError());
        return FAILURE;
    }

    return EXIT_SUCCESS;
}

void drawGraphics(SDL_Window **Window, SDL_Surface **WindowSurface, SDL_Surface **Image) {
    SDL_BlitSurface(*Image, NULL, *WindowSurface, NULL);
    if (SDL_UpdateWindowSurface(*Window) != SUCCESS) {
        LOGERR("SDL_BlitSurface failed! Reason: %s", SDL_GetError());
    }

    SDL_Delay(10000);
}

void deinitGame(SDL_Window **Window, SDL_Surface **WindowSurface) {
    if (*WindowSurface != NULL) {
        SDL_FreeSurface(*WindowSurface);
    }
    if (*Window != NULL) {
        SDL_DestroyWindow(*Window);
    }
    SDL_Quit();
}