//
// Created by Iordan Tonchev on 9.11.21.
//
#include <SDL.h>
#include <stdlib.h>

#include "Graphics/ImageLayers.h"
#include "Physics/Vector2D.h"
#include "Utils/include/containers/Vector.h"

/*------------- PRIVATE: -----------------------*/

#define INITIAL_TILES_COUNT 5

struct LayeredImage2D {
    struct Vector TexturesContainer;
    int32_t Width;
    int32_t Height;
    int32_t LayerIndex;
    float_t ScrollSpeed;
    BOOL isLooped;
    BOOL isFlipped;
};


/*------------- PUBLIC: -----------------------*/

void initLayeredImage(ImageLayer **self, int32_t ImageCount, int32_t Width, int32_t Height, int32_t LayerIndex,
                      int32_t ScrollSpeed, BOOL Looped, BOOL Flipped) {
    *self = (ImageLayer *) malloc(sizeof(struct LayeredImage2D));
    initVector(&(*self)->TexturesContainer, ImageCount);
    (*self)->Width = Width;
    (*self)->Height = Height;
    (*self)->LayerIndex = LayerIndex;
    (*self)->ScrollSpeed = ScrollSpeed;
    (*self)->isLooped = Looped;
    (*self)->isFlipped = Flipped;
}

void deinitLayeredImage(ImageLayer **self) {
    if (*self != NONE) {
        freeVector(&(*self)->TexturesContainer);
        free(*self);
        *self = NONE;
    }
}

struct Vector* getTexturesContainer (ImageLayer *self) {
    return &self->TexturesContainer;
}

void setScrollSpeed(ImageLayer **self, float_t ImageScrollSpeed) {
    (*self)->ScrollSpeed = ImageScrollSpeed;
}

float_t getScrollSpeed(const ImageLayer **self) {
    return (*self)->ScrollSpeed;
}

void setLayerIndex(ImageLayer **self, int32_t index) {
    (*self)->LayerIndex = index;
}

int32_t getLayerIndex(const ImageLayer *self) {
    return self->LayerIndex;
}

void setImageLoop(ImageLayer **self, BOOL loop) {
    (*self)->isLooped = loop;
}

void flipImage(ImageLayer **self, BOOL FlipFlag) {
    (*self)->isFlipped = FlipFlag;
}