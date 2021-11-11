//
// Created by Iordan Tonchev on 8.10.21.
//

#ifndef SDL_GAME_GAMEENGINECORE_H
#define SDL_GAME_GAMEENGINECORE_H
#include <stdint.h>
#include <stdio.h>
#include "GameObject/GameObject2D.h"
#include "Actors/BaseCharacter.h"
#include "Actors/PlayerCharacter.h"
#include "Core/Camera2D.h"


int8_t SDLLoader(playerActor *Player);
void SDLUnloader();
void DrawCharacter(int32_t Event, float *DeltaTime, Character *BaseCharacter);
void DrawCamera(Camera *Camera);

#endif //SDL_GAME_GAMEENGINECORE_H
