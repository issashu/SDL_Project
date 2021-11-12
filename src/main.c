//System headers
#include <stdlib.h>

//Misc 3rd party libs

//Own libs and headers
#include "game_engine/include/Core/MainGameLoop.h"

int main() {
    if(mainGame()){
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
