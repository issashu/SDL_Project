//
// Created by Iordan Tonchev on 9.11.21.
//

#ifndef SDL_GAME_IMAGELAYERS_H
#define SDL_GAME_IMAGELAYERS_H

typedef struct LayeredImage2D ImageLayer;

void initLayeredImage (ImageLayer **self);
void deinitLayeredImage (ImageLayer **self);

#endif //SDL_GAME_IMAGELAYERS_H
