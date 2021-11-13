//
// Created by Iordan Tonchev on 12.11.21.
//

#ifndef SDL_GAME_DRAWPARALAXBACKGROUNDS_H
#define SDL_GAME_DRAWPARALAXBACKGROUNDS_H

#include "Graphics/ImageLayers.h"
#include "Graphics/GraphicsRenderer2D.h"
#include "Managers/TextureManager.h"

void LoadImageLayer(ImageLayer **BackgroundSet, int32_t LayerIndex, int32_t ImageCount, int32_t Width, int32_t Height,
                    int32_t ScrollSpeed, BOOL isLooped, BOOL isFlipped, STRING *ImageMap);

#endif //SDL_GAME_DRAWPARALAXBACKGROUNDS_H
