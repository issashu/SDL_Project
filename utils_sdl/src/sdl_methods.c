//
// Created by Iordan Tonchev on 6.10.21.
//
#include <SDL.h>
#include "include/sdl_methods.h"
#include "include/defines.h"
#include "utils/Log.h"

void initSDL(){
    //TODO Add this as main entry point for the SDL lib
}

int32_t initScreen(SDL_Window **Window, SDL_Surface **WindowSurface) {
    if (SDL_Init(SDL_INIT_VIDEO) != SUCCESS) {
        LOGERR("SDL_Init() failed! Reason: %s", SDL_GetError());
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

void deinitGame(SDL_Window **Window, SDL_Surface **WindowSurface) {
    if (*WindowSurface != NULL) {
        SDL_FreeSurface(*WindowSurface);
    }
    if (*Window != NULL) {
        SDL_DestroyWindow(*Window);
    }
    SDL_Quit();
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
