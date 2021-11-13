//
// Created by Iordan Tonchev on 4.11.21.
//
#include <stdlib.h>
#include "Actors/PlayerCharacter.h"
#include "utils/defines.h"


/*------------- PRIVATE: -----------------------*/
struct PlayerCharacter {
    Character *baseCharacter;
    STRING spriteSheetPath;
    STRING playerName;
};

/*------------- PUBLIC: -----------------------*/

void initPlayerActor(playerActor **self, char *Name) {
    *self = (playerActor *) malloc(sizeof(struct PlayerCharacter));
    (*self)->spriteSheetPath = ASSETS_PATH "images/character_anim.png";
    (*self)->playerName = Name;
    initCharacter(&(*self)->baseCharacter, (*self)->spriteSheetPath);
}

void deinitPlayerActor(playerActor **self) {
    if (*self != NONE) {
        deinitCharacter(&(*self)->baseCharacter);
        free(*self);
        *self = NONE;
    }
}

Character* getBaseChar (struct PlayerCharacter *self){
    return self->baseCharacter;
}

STRING getPlayerName(playerActor *self) {
    return self->playerName;
}

STRING getSpriteSheetPath (playerActor *self) {
    return self->spriteSheetPath;
}

void setPlayerName(playerActor *self, STRING Name) {
    self->playerName = Name;
}

int32_t getPlayerState (playerActor *self) {
    return getState(self->baseCharacter);
}

void setPlayerState(playerActor *self, int32_t state){
    setState(self->baseCharacter, state);
}



