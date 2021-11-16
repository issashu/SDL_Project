//
// Created by Iordan Tonchev on 7.10.21.
//

#ifndef SDL_GAME_EVENTMANAGER_H
#define SDL_GAME_EVENTMANAGER_H

#include <stdio.h>
#include <stdint.h>
#include "Utils/include/Defines.h"
#include "Actors/PlayerCharacter.h"


//TODO Apply singleton

typedef struct EventManager{
    void (*handleCharacterEvent)(BOOL*, Character*, SDL_Event*);
    void (*updateCharacter)(Character*, const float*, SDL_Renderer**, SDL_Texture*);
} EventHandler;

EventHandler* getCharacterEventHandler();
void deleteCharacterHandler();

void characterEventHandler(BOOL *isRunning, Character *BaseCharacter, SDL_Event *gameEventAI);
void updateCharacterActor(Character *BaseCharacter,
                          const float *DeltaTime,
                          SDL_Renderer **GfxRenderer,
                          SDL_Texture *Texture);

#endif //SDL_GAME_EVENTMANAGER_H
