//
// Created by Iordan Tonchev on 22.10.21.
//

#include "GameObject/GameObject2D.h"
#include "Actors/BaseCharacter.h"

/*------------- PRIVATE: -----------------------*/

struct CharacterActor{
GameObject2D *Base2D;
int32_t Health;
int32_t Mana;
STRING spriteSheet;
//TODO Add some stats and function pointers for methods
};

/*------------- PUBLIC: -----------------------*/

void initCharacter(Character *self, char *texturePath) {
    initObject(self->Base2D);
    self->Health = 100;
    self->Mana = 100;
    self->spriteSheet = texturePath;
}

int32_t getHealth (Character *self) {
    return self->Health;
}

int32_t getMana (Character *self) {
    return self->Mana;
}

STRING getSpriteSheet(Character *self) {
    return self->spriteSheet;
}

void setHealth(Character *self, int32_t HP){
    self->Health = HP;
}

void takeDamage(Character *self, int32_t Dmg) {
    self->Health -=Dmg;
}

void healDamage(Character *self, int32_t Heal) {
    self->Health +=Heal;
}

void moveCharacter(Character *self, float DeltaTime, Vector2D *Force, Vector2D *Friction) {
    updateObject(self->Base2D,DeltaTime, Force, Friction);
}