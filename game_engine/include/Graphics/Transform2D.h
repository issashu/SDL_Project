//
// Created by Iordan Tonchev on 21.10.21.
//

#ifndef SDL_GAME_TRANSFORM2D_H
#define SDL_GAME_TRANSFORM2D_H

/**
 * Transform2D holds the information for an object position
 * in space.
 * Attach this as substructure to a Game Object.
 */
typedef struct Transform2D {
    float X;
    float Y;
    void (*transX)(float);
    void (*transY)(float);
    void (*trans2D)(float, float);
} Transform2D;

#endif //SDL_GAME_TRANSFORM2D_H
