//System headers
#include <stdlib.h>

//Misc 3rd party libs

//Own libs and headers
#include "include/gameLoop.h"

int main() {
    if(gameLoop()){
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
