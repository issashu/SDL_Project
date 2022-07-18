//
// Created by Iordan Tonchev on 14.11.21.
//

#ifndef SDL_GAME_BASEPLATFORM2D_H
#define SDL_GAME_BASEPLATFORM2D_H

#include <stdint.h>
#include "Utils/include/Defines.h"
#include "Graphics/GraphicsRenderer2D.h"
#include "GameObject/GameObject2D.h"

typedef struct BasePlatform2D BasePlatform2D;

void
initBasePlatform(BasePlatform2D **self, char *TexturePath, char *Tag, int32_t Width, int32_t Height, int32_t Health,
                 SDL_Renderer *GfxRenderer, float SpawnX, float SpawnY, uint32_t PlatformID);
void deinitBasePlatform(BasePlatform2D **self);
STRING getTexturePath(BasePlatform2D *self);
STRING getTag(BasePlatform2D *self);
GameObject2D* getBaseObject (BasePlatform2D *self);
int32_t getWidth(BasePlatform2D *self);
int32_t getHeight(BasePlatform2D *self);
int32_t checkHealth(BasePlatform2D *self);
void setTexturePath (BasePlatform2D **self, STRING texturePath);
void setTag (BasePlatform2D **self, STRING tag);

#endif //SDL_GAME_BASEPLATFORM2D_H
