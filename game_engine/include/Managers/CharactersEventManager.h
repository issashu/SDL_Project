//
// Created by Iordan Tonchev on 7.10.21.
//

#ifndef SDL_GAME_CHARACTERSEVENTMANAGER_H
#define SDL_GAME_CHARACTERSEVENTMANAGER_H

#include <stdio.h>
#include <stdint.h>
#include "Utils/include/Defines.h"
#include "Actors/PlayerCharacter.h"


//TODO Apply singleton

typedef struct CharactersEventManager{
    void (*handleCharacterEvent)(BOOL*, Character*, SDL_Event*);
    void (*updateCharacter)(Character*, const float*, SDL_Renderer**, SDL_Texture*, BOOL*);
} CharacterEventHandler;

CharacterEventHandler* getCharacterEventHandler();
void deleteCharacterHandler();

void characterEventHandler(BOOL *isRunning, Character *BaseCharacter, SDL_Event *gameEventAI);
void
updateCharacterActor(Character *BaseCharacter, const float *DeltaTime, SDL_Renderer **GfxRenderer, SDL_Texture *Texture,
                     BOOL *isRunning);

#endif //SDL_GAME_CHARACTERSEVENTMANAGER_H
