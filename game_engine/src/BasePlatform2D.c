//
// Created by Iordan Tonchev on 14.11.21.
//

#include "GameObject/Platforms/BasePlatform2D.h"


/*------------- PRIVATE: -----------------------*/

struct BasePlatform2D {
    GameObject2D *BaseObject;
    STRING TexturePath;
    STRING Tag;
    int32_t Width;
    int32_t Height;
    int32_t Health;
};


/*------------- PUBLIC: -----------------------*/

void
initBasePlatform(BasePlatform2D **self, char *TexturePath, char *Tag, int32_t Width, int32_t Height, int32_t Health,
                 SDL_Renderer *GfxRenderer, float SpawnX, float SpawnY) {
    *self = (BasePlatform2D *) malloc(sizeof(struct BasePlatform2D));
    (*self)->TexturePath = TexturePath;
    (*self)->Tag = Tag;
    (*self)->Width = Width;
    (*self)->Height = Height;
    (*self)->Health = Health;
    initObject(&(*self)->BaseObject, 0, (*self)->Width, (*self)->Height, GfxRenderer, (*self)->TexturePath, SpawnX, SpawnY);
}

void deinitBasePlatform(BasePlatform2D **self) {
    deinitObject(&(*self)->BaseObject);
    free(*self);
    *self = NONE;
}

STRING getTexturePath(BasePlatform2D *self){
    return self->TexturePath;
}

STRING getTag(BasePlatform2D *self) {
    return self->Tag;
}

int32_t getWidth(BasePlatform2D *self) {
    return self->Width;
}

int32_t getHeight(BasePlatform2D *self) {
    return self->Height;
}

int32_t checkHealth(BasePlatform2D *self) {
    return self->Health;
}

GameObject2D* getBaseObject (BasePlatform2D *self) {
    return self->BaseObject;
}

void setTexturePath (BasePlatform2D **self, STRING texturePath) {
    (*self)->TexturePath = texturePath;
}

void setTag (BasePlatform2D **self, STRING tag) {
    (*self)->Tag = tag;
}