//System headers
#include <stdio.h>
#include <stdlib.h>

//Misc 3rd party libs
#include <SDL.h>

//Own libs
#include "Log.h"
#include "defines.h"
#include "sdl_methods.h"
#include "event_poll.h"

int main() {
    const STRING ImagePath = "../assets/Images/hello.bmp";
    //struct SDLWindow AppWindow;
    //TODO replace globals with the local structure
    SDL_Window *gWindow = NULL;
    SDL_Surface *gScreenSurface = NULL;
    SDL_Surface *gImage = NULL;
    SDL_Event **gameEvent = NULL;

    gImage = SDL_LoadBMP(ImagePath);
    //TODO Take out all error checks in a separate function ot move that in the init
    if (initScreen(&gWindow, &gScreenSurface) != SUCCESS) {
        LOGERR("initScreen() failed.");
        //TODO Add info for file, line and path
    }

    if (loadResources(&gImage, &ImagePath) != SUCCESS) {
        LOGERR("loadResources() failed.");
        //TODO Add info for file, line and path
    }

    while (eventHandler(gameEvent) == 0){
        drawGraphics(&gWindow, &gScreenSurface, &gImage);
    }
    deinitGame(&gWindow, &gScreenSurface);

    return EXIT_SUCCESS;
}
