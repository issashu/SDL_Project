//System headers
#include <stdio.h>
#include <stdlib.h>

//Misc 3rd party libs
#include <SDL.h>

//Own libs
#include "utils/Log.h"
#include "include/sdl_methods.h"
#include "include/defines.h"

int main() {
    const STRING ImagePath = "../assets/Images/hello.bmp";
    struct SDLWindow AppWindow;
    //TODO replace globals with the local structure
    SDL_Window *gWindow = NULL;
    SDL_Surface *gScreenSurface = NULL;
    SDL_Surface *gImage = NULL;

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
    drawGraphics(&gWindow, &gScreenSurface, &gImage);
   //getchar();
    deinitGame(&gWindow, &gScreenSurface);

    return EXIT_SUCCESS;
}
