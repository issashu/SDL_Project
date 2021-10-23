//
// Created by Iordan Tonchev on 23.10.21.
//

#ifndef SDL_GAME_WINDOWMANAGER_H
#define SDL_GAME_WINDOWMANAGER_H

#include <utils/defines.h>

typedef struct WindowManager{
    struct SDLWindow *Window;
}WindowController;

int32_t initScreen(SDL_Window **Window, int32_t Width, int32_t Height);

#endif //SDL_GAME_WINDOWMANAGER_H
