//
// Created by Iordan Tonchev on 4.11.21.
//
#include <stdlib.h>
#include "Actors/Player.h"

//FIXME Encapsulation breaks badly with init functions, though only seeing publics
void initPlayer(playerActor *player){
    player = (playerActor *) malloc (sizeof(struct Player));
    player->spriteSheetPath = ASSETS_PATH "images/character_anim.png";
    player->AnimationSpeed = 150;
    player->playerName = "Issashu";
    initCharacter(&player->baseCharacter, player->playerName, player->spriteSheetPath);
}
