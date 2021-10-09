//System headers
#include <stdio.h>
#include <stdlib.h>

//Misc 3rd party libs


//Own libs and headers
//TODO Check why cmake doesn't help with paths
#include "include/gameLoop.h"

int main() {

    SDLLoader();
    gameLoop();
    SDLUnloader();

    return EXIT_SUCCESS;
}
