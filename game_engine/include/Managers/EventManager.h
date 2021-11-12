//
// Created by Iordan Tonchev on 7.10.21.
//

#ifndef SDL_GAME_EVENTMANAGER_H
#define SDL_GAME_EVENTMANAGER_H

#include <stdio.h>
#include <stdint.h>
#include <utils/defines.h>
#include <Actors/PlayerCharacter.h>


//TODO Apply singleton
void characterEventHandler(BOOL *isRunning, Character *BaseCharacter, SDL_Event *gameEventAI);
void updatePlayer(Character *BaseCharacter,
                  const float *DeltaTime,
                  SDL_Renderer **GfxRenderer,
                  SDL_Texture **Texture);

#endif //SDL_GAME_EVENTMANAGER_H
