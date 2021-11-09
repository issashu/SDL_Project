//
// Created by Iordan Tonchev on 9.11.21.
//
#include <SDL.h>
#include <stdlib.h>

#include "Graphics/ImageLayers.h"
#include "Physics/Vector2D.h"
#include "utils/defines.h"

/*------------- PRIVATE: -----------------------*/
struct LayeredImage2D {
    STRING TexturePath;
    Vector2D Offset;
    Vector2D Scale;
    int32_t Width;
    int32_t Height;
    BOOL isLooped;
    float_t ScrollSpeed;
    SDL_RendererFlip isFlipped;
};


/*------------- PUBLIC: -----------------------*/

void initLayeredImage (ImageLayer **self) {
    *self = (ImageLayer*) malloc (sizeof(struct LayeredImage2D));
    (*self)->TexturePath = "";
    initVector2D(&(*self)->Offset);
    initVector2D(&(*self)->Scale);
    (*self)->Width = 0;
    (*self)->Height = 0;
    (*self)->isLooped = FALSE;
    (*self)->ScrollSpeed = 0;
    (*self)->isFlipped = SDL_FLIP_NONE;
}

void deinitLayeredImage (ImageLayer **self) {
    if(*self != NONE) {
        deinitVector2D(&(*self)->Offset);
        deinitVector2D(&(*self)->Scale);
        free(*self);
        *self = NONE;
    }
}

void setScrollSpeed (ImageLayer **self, float_t ImageScrollSpeed){
    (*self)->ScrollSpeed = ImageScrollSpeed;
}
float_t* getScrollSpeed(ImageLayer **self) {
    return &(*self)->ScrollSpeed;
}

void loopImage(ImageLayer **self, BOOL loop){
    (*self)->isLooped = loop;
}

void flipImage(ImageLayer **self, int32_t FlipFlag) {
    (*self)->isFlipped = FlipFlag;
} 
//TODO Put setters and getters

