//
// Created by Iordan Tonchev on 13.11.21.
//

#include "Managers/GameStateManager.h"
#include "Core/GameScenes/MainLevel.h"
#include "utils/defines.h"


/*1. GAME LOAD & GAMESTATEMANAGER ON
 * 1.1 LOAD ASSETS
 * 1.2 START MAIN LOOP
 * 2. MAIN MENU
 * 2.1 LOAD BACKGROUND
 * 2.2 MUSIC
 * 2.3 ANIMATION?
 * 2.4 BUTTONS
 * 2.5 SETTINGS?
 * 3. LOAD LEVEL
 * 3.1 INIT CHARACTER
 * 3.2 INIT ENEMIES
 * 3.3 INIT OBJECTS
 * 3.4 INIT BACKGROUNDS
 * 4 START MAIN LOOP
 * 4.0.1 CLEAR RENDERER
 * 4.1 DRAW BACKGROUND LAYERS BEHIND HERO
 * 4.2 REGISTER PLAYER EVENTS
 * 4.3 REGISTER ENEMY EVENTS
 * 4.3.1 RUN PHYSICS AND CHECKS
 * 4.4 DRAW ENEMIES AND HERO (SAME LAYER?)
 * 4.5 DRAW ANY FOREGROUND LAYERS
 * 4.6 PRESENT RENDERER AND REPEAT LOOP
 * 4.7 ON EXIT EVENT DE INIT ALL INITIALISED OBJECTS AND ENTITIES
 * 4.8 DESTROY TEXTURES AND CLEAR SCREEN
 * 4.9 EXIT GAME
 *
*/

/*------------- PRIVATE: -----------------------*/
static GameStateManager *self = NONE;
uint8_t CurrentGameState = 0;

BOOL switchGameState(uint8_t State);
uint8_t getGameState ();

/*------------- PUBLIC: -----------------------*/

GameStateManager* getGameStateManager() {
    if (self==NONE) {
        self = (GameStateManager *)malloc(sizeof(struct GameStateManager));
        self->switchState= &switchGameState;
        self->getState=&getGameState;
    }

    return self;
}

void deinitGameStateManager() {
    if (self != NONE){
        self->switchState = NONE;
        self->getState = NONE;
        free(self);
        self = NONE;
    }
}

/*------------- IMPLEMENTATION: -----------------------*/

BOOL switchGameState(uint8_t State) {
    //TODO Make sure all game functions return exit status to use here
    BOOL ExitStatus = EXIT_SUCCESS;
    uint8_t GameState = State;
    switch(GameState){
        case NO_STATE:
        case MAIN_SCREEN:
            break;

        case MAIN_GAME:
            ExitStatus = mainGame();
            break;

        case EXIT_GAME:
            break;

        case ALL_STATES:
        default:
            GameState = EXIT_GAME;
            break;
    }

    return ExitStatus;
}

uint8_t getGameState ()  {
    return CurrentGameState;
}
