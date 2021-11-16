//System headers

//Misc 3rd party libs

//Own libs and headers
#include "game/include/main.h"

int main() {
    GameStateManager* Manager = getGameStateManager();
    //FIXME Magic number fix once we have main menu
    if(Manager->switchState(2)) {
        return EXIT_FAILURE;
    }
    deinitGameStateManager();
    return EXIT_SUCCESS;
}
