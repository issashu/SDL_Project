//
// Created by Iordan Tonchev on 9.11.21.
//

#ifndef SDL_GAME_IMAGELAYERS_H
#define SDL_GAME_IMAGELAYERS_H

#include <stdint.h>

#include "Utils/include/Defines.h"

/**
 * A Vector-like container with Background images.
 * Set it's LayerIndex variable to the background layer you want this drawn to.
 */
typedef struct LayeredImage2D ImageLayer;

void initLayeredImage(ImageLayer **self, int32_t ImageCount, int32_t Width, int32_t Height, int32_t LayerIndex,
                      int32_t ScrollSpeed, BOOL Looped, BOOL Flipped);

void deinitLayeredImage(ImageLayer **self);

struct Vector* getTexturesContainer (ImageLayer *self);

void setScrollSpeed(ImageLayer **self, float ImageScrollSpeed);

float getScrollSpeed(const ImageLayer **self);

void setLayerIndex(ImageLayer **self, int32_t index);

int32_t getLayerIndex(const ImageLayer *self);

void setImageLoop(ImageLayer **self, BOOL loop);

void flipImage(ImageLayer **self, BOOL FlipFlag);

#endif //SDL_GAME_IMAGELAYERS_H
