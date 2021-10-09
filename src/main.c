//System headers
#include <stdio.h>
#include <stdlib.h>

//Misc 3rd party libs


//Own libs and headers
#include "sdl_command.h"

int main() {
    SDLLoader();
    SDLUnloader();
/*
    const STRING ImagePath = "../assets/Images/hello.bmp";
    Image = SDL_LoadBMP(ImagePath);

    if (loadResources(&Image, &ImagePath) != SUCCESS) {
        LOGERR("loadResources() failed.");
        //TODO Add info for file, line and path
    }

    while (eventHandler(&gameEvent) == 0){
        drawGraphics(&Window, &screenSurface, &Image);
    }
*/
    return EXIT_SUCCESS;
}
