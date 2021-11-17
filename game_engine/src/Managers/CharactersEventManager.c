//
// Created by Iordan Tonchev on 7.10.21.
//

#include <SDL_events.h>
#include "Managers/CharactersEventManager.h"
#include "Core/GameEngineCore.h"
#include "Actors/BaseCharacter.h"
#include "Utils/include/Defines.h"

/*------------- PRIVATE: -----------------------*/
void keyboardEvent(BOOL *isRunning, Character *BaseCharacter, const u_int8_t *gameKeyStates);

void characterEventHandler(BOOL *isRunning, Character *BaseCharacter, SDL_Event *gameEventAI);

void updateCharacterActor(Character *BaseCharacter,
                          const float *DeltaTime,
                          SDL_Renderer **GfxRenderer,
                          SDL_Texture *Texture);

static CharacterEventHandler *self = NONE;

/*------------- PUBLIC: -----------------------*/

CharacterEventHandler *getCharacterEventHandler() {
    if (self == NONE) {
        self = (CharacterEventHandler *) malloc(sizeof(struct CharactersEventManager));
        self->handleCharacterEvent = &characterEventHandler;
        self->updateCharacter = &updateCharacterActor;
    }

    return self;
}

void deleteCharacterHandler() {
    if (self != NONE) {
        free(self);
        self = NONE;
    }
}


/*------------- IMPLEMENTATION: -----------------------*/
void characterEventHandler(BOOL *isRunning, Character *BaseCharacter, SDL_Event *gameEventAI) {
//Player character does not send a default event; AI characters will.
//FIXME FIX the logic below to reflect between player and AI
    if (gameEventAI == NONE) {
        SDL_Event gameEvent;
        const u_int8_t *gameKeyStates = NONE;
        while (SDL_PollEvent(&gameEvent)) {
            switch (gameEvent.type) {
                case SDL_QUIT:
                    *isRunning = FALSE;
                    break;

                case SDL_CONTROLLERBUTTONDOWN:
                case SDL_KEYDOWN:
                    gameKeyStates = SDL_GetKeyboardState(NULL);
                    keyboardEvent(isRunning, BaseCharacter, gameKeyStates);
                    break;

                case SDL_CONTROLLERBUTTONUP:
                case SDL_KEYUP:
                    setState(BaseCharacter, IDLE_STATE);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEMOTION:
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEWHEEL:
                case SDL_MOUSEWHEEL_FLIPPED:
                case SDL_MOUSEWHEEL_NORMAL:
                    break;

                default:
                    break;
            }
        }
    } else {
        return;
    }

}

void keyboardEvent(BOOL *isRunning, Character *BaseCharacter, const u_int8_t *gameKeyStates) {
    //TODO ADD DOXYGEN and set some default key event (also might be having slight delay because of pump
    //TODO Find a way to automate indexing. Maybe object struct should know the index of its texture
    // https://cpp.hotexamples.com/examples/-/-/SDL_GetKeyboardState/cpp-sdl_getkeyboardstate-function-examples.html
    if (gameKeyStates[SDL_SCANCODE_W] != 0) {
        setState(BaseCharacter, JUMPING_UP);
    }
    if (gameKeyStates[SDL_SCANCODE_E]) {
        setState(BaseCharacter, JUMPING_RIGHT);
    }
    if (gameKeyStates[SDL_SCANCODE_Q]) {
        setState(BaseCharacter, JUMPING_LEFT);
    }
    if (gameKeyStates[SDL_SCANCODE_D]) {
        setState(BaseCharacter, RUNNING_RIGHT);
    }
    if (gameKeyStates[SDL_SCANCODE_A]) {
        setState(BaseCharacter, RUNNING_LEFT);
    }
    if (gameKeyStates[SDL_SCANCODE_S]) {
        setState(BaseCharacter, CROUCHING);
    }
    if (gameKeyStates[SDL_SCANCODE_S] && gameKeyStates[SDL_SCANCODE_D]) {
        setState(BaseCharacter, CRAWLING_RIGHT);
    }
    if (gameKeyStates[SDL_SCANCODE_S] && gameKeyStates[SDL_SCANCODE_A]) {
        setState(BaseCharacter, CRAWLING_LEFT);
    }
    if (gameKeyStates[SDL_SCANCODE_SPACE]) {
        setState(BaseCharacter, ATTACKING);
    }
    if (gameKeyStates[SDL_SCANCODE_ESCAPE]) {
        *isRunning = FALSE;
    }
}

void updateCharacterActor(Character *BaseCharacter, const float *DeltaTime, SDL_Renderer **GfxRenderer,
                          SDL_Texture *Texture) {
    static Vector2D Force;
    static Vector2D Friction;
    initVector2D(&Force);
    initVector2D(&Friction);
    switch (getState(BaseCharacter)) {
        case IDLE_STATE:
            if (Force.Y <= 0) {
                Force.Y = 0;
            } else {
                Force.Y -= WORLD_GRAVITY * (*DeltaTime);
                moveCharacter(BaseCharacter, DeltaTime, &Force, &Friction);
                DrawCharacter(IDLE_STATE, DeltaTime, BaseCharacter, GfxRenderer, Texture);
            }
            break;
        case JUMPING_UP:
            if (getAirborne(getBaseObj(BaseCharacter)) == FALSE) {
                GameObject2D *ObjProxy = getBaseObj(BaseCharacter);
                setAirborne(&ObjProxy, TRUE);
                Force.set(&Force, 0.0, -3.0);
                moveCharacter(BaseCharacter, DeltaTime, &Force, &Friction);
                DrawCharacter(SDL_SCANCODE_UP, DeltaTime, BaseCharacter, GfxRenderer, Texture);
            }
            break;
        case JUMPING_LEFT:
            Force.set(&Force, -2.0, -3.0);
            moveCharacter(BaseCharacter, DeltaTime, &Force, &Friction);
            DrawCharacter(SDL_SCANCODE_UP, DeltaTime, BaseCharacter, GfxRenderer, Texture);
            break;
        case JUMPING_RIGHT:
            Force.set(&Force, 2.0, -3.0);
            moveCharacter(BaseCharacter, DeltaTime, &Force, &Friction);
            DrawCharacter(SDL_SCANCODE_UP, DeltaTime, BaseCharacter, GfxRenderer, Texture);
            break;
        case JUMPING_DOWN:
            Force.set(&Force, 0.0, 2.0);
            moveCharacter(BaseCharacter, DeltaTime, &Force, &Friction);
            DrawCharacter(SDL_SCANCODE_UP, DeltaTime, BaseCharacter, GfxRenderer, Texture);
            break;
        case CROUCHING:
            //TODO Add methods to shrink hitbox
            Force.set(&Force, 0.0, 0.0);
            moveCharacter(BaseCharacter, DeltaTime, &Force, &Friction);
            DrawCharacter(SDL_SCANCODE_DOWN, DeltaTime, BaseCharacter, GfxRenderer, Texture);
            break;
        case CRAWLING_LEFT:
            Force.set(&Force, -1.0, 0.0);
            moveCharacter(BaseCharacter, DeltaTime, &Force, &Friction);
            DrawCharacter(SDL_SCANCODE_DOWN, DeltaTime, BaseCharacter, GfxRenderer, Texture);
            break;
        case CRAWLING_RIGHT:
            Force.set(&Force, 1.0, 0.0);
            moveCharacter(BaseCharacter, DeltaTime, &Force, &Friction);
            DrawCharacter(SDL_SCANCODE_DOWN, DeltaTime, BaseCharacter, GfxRenderer, Texture);
            break;
        case DEAD:
            break;
        case RUNNING_LEFT:
            Force.set(&Force, -2.0, 0.0);
            moveCharacter(BaseCharacter, DeltaTime, &Force, &Friction);
            DrawCharacter(SDL_SCANCODE_LEFT, DeltaTime, BaseCharacter, GfxRenderer, Texture);
            break;
        case RUNNING_RIGHT:
            Force.set(&Force, 2.0, 0.0);
            moveCharacter(BaseCharacter, DeltaTime, &Force, &Friction);
            DrawCharacter(SDL_SCANCODE_RIGHT, DeltaTime, BaseCharacter, GfxRenderer, Texture);
            break;
        case ATTACKING:
            Force.set(&Force, (0.5 * getHorrizFlip(getBaseObj(BaseCharacter))), 0.0);
            moveCharacter(BaseCharacter, DeltaTime, &Force, &Friction);
            DrawCharacter(SDL_SCANCODE_SPACE, DeltaTime, BaseCharacter, GfxRenderer, Texture);
            break;
        default:
            break;
    }
}