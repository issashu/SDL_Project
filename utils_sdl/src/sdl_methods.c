//
// Created by Iordan Tonchev on 6.10.21.
//

#include "Core/sdl_methods.h"
#include "Core/sdl_default_app_settings.h"
#include "utils/defines.h"
#include "utils/Log.h"

int32_t initScreen(SDL_Window **Window) {
    if (SDL_Init(SDL_INIT_VIDEO) != SUCCESS) {
        LOGERR("SDL_Init_VIDEO() failed! Reason: %s", SDL_GetError());
        //TODO Add filename, path and line number to the logger
        //TODO Why do we use a macro in LOGGER?
        return FAILURE;
    }
    //TODO REMOVE THE MAGIC NUMBERS AS PARAMS
    *Window = SDL_CreateWindow("Metroidvania", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, \
                                WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (*Window == NULL) {
        LOGERR("SDL_CreateWindow failed! Reason: %s", SDL_GetError());
        //TODO Add filename, path and line number to the logger
        return FAILURE;
    }


//    *WindowSurface = SDL_GetWindowSurface(*Window);
//    if (*WindowSurface == NULL) {
//        LOGERR("SDL_GetWindowSurface has failed! Reason: %s", SDL_GetError());
//        //TODO Add filename, path and line number to the logger
//        return FAILURE;
//    }

    return EXIT_SUCCESS;
}

int32_t initText(){
    if (TTF_Init() != SUCCESS) {
        LOGERR("TTF_Init() failed! Reason: %s", SDL_GetError());
        //TODO Add filename, path and line number to the logger
        //TODO Why do we use a macro in LOGGER?
        return FAILURE;
    }

    return SUCCESS;
}

//FIXME Do we really need this one? IMG_Load works without it just fine
int32_t initTextures(){
    const int32_t imgType = IMG_INIT_PNG;

    if (! (IMG_Init(imgType) & imgType)) {
        LOGERR("SDL_image could not be initialised! SDL_image Error: %s",
               IMG_GetError());
        return FAILURE;
    }

    return SUCCESS;
}

int32_t initTimers(){
    if (SDL_Init(SDL_INIT_TIMER) != SUCCESS) {
        LOGERR("SDL_Init_TIMER() failed! Reason: %s", SDL_GetError());
        //TODO Add filename, path and line number to the logger
        //TODO Why do we use a macro in LOGGER?
        return FAILURE;
    }

    return SUCCESS;
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

    return SUCCESS;
}

//https://www.youtube.com/watch?v=yFLa3ln16w0&t=1025s
// FORGOT THE DOUBLE BUFFER >.>
//TODO Free up render resources on deinit!!!!
void drawGraphics(SDL_Renderer **Renderer, SDL_Texture *Texture) {
    SDL_RenderCopy(*Renderer, Texture, NULL, NULL);
    SDL_RenderPresent(*Renderer);
}

void deinitGame(SDL_Window **Window, SDL_Surface **Image) {
    if (*Image != NULL) {
        SDL_FreeSurface(*Image);
    }
    if (*Window != NULL) {
        SDL_DestroyWindow(*Window);
    }
    SDL_Quit();
}