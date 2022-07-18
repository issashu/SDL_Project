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

void
updateCharacterActor(Character *BaseCharacter, const float *DeltaTime, SDL_Renderer **GfxRenderer, SDL_Texture *Texture,
                     BOOL *isRunning);

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
    const u_int8_t *gameKeyStates = NONE;
    SDL_Event gameEvent;
    while (SDL_PollEvent(&gameEvent)) {
        if (gameEventAI != NONE) {
            gameEvent.type = gameEventAI->type;
        }
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
}

void keyboardEvent(BOOL *isRunning, Character *BaseCharacter, const u_int8_t *gameKeyStates) {
    if (gameKeyStates[SDL_SCANCODE_W] != 0) {
        if (getAirborne(getBaseObj(BaseCharacter)) == FALSE) {
            GameObject2D *ObjProxy = getBaseObj(BaseCharacter);
            setAirborne(&ObjProxy, TRUE);
            setState(BaseCharacter, JUMPING_UP);
        }
    }
    if (gameKeyStates[SDL_SCANCODE_E]) {
        if (getAirborne(getBaseObj(BaseCharacter)) == FALSE) {
            GameObject2D *ObjProxy = getBaseObj(BaseCharacter);
            setAirborne(&ObjProxy, TRUE);
            setState(BaseCharacter, JUMPING_RIGHT);
        }
    }
    if (gameKeyStates[SDL_SCANCODE_Q]) {
        if (getAirborne(getBaseObj(BaseCharacter)) == FALSE) {
            GameObject2D *ObjProxy = getBaseObj(BaseCharacter);
            setAirborne(&ObjProxy, TRUE);
            setState(BaseCharacter, JUMPING_LEFT);
        }
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

void
updateCharacterActor(Character *BaseCharacter, const float *DeltaTime, SDL_Renderer **GfxRenderer, SDL_Texture *Texture,
                     BOOL *isRunning) {
    static BOOL isInit = FALSE;
    static uint8_t TimeInterval = 0;
    SDL_Event tempEvent;
    tempEvent.type = SDL_KEYUP;
    static Vector2D Force;
    static Vector2D Friction;

    if (!isInit) {
        initVector2D(&Force);
        initVector2D(&Friction);
        isInit = TRUE;
    }

    switch (getState(BaseCharacter)) {
        case IDLE_STATE:
            if (Force.Y < 0) {
                Force.Y += WORLD_GRAVITY * (*DeltaTime);
            }
            if (Force.X != 0) {
                Force.X += (-Force.X) * (*DeltaTime);
            }
            moveCharacter(BaseCharacter, DeltaTime, &Force, &Friction);
            DrawCharacter(rand()%ALL_ALIVE_STATES+1, DeltaTime, BaseCharacter, GfxRenderer, Texture);
            break;
        case JUMPING_UP:
            Force.set(&Force, 0.2, JUMP_FORCE);
            for (uint32_t timer = 0; timer < JUMP_FRAMES; timer++) {
                DrawCharacter(SDL_SCANCODE_UP, DeltaTime, BaseCharacter, GfxRenderer, Texture);
                moveCharacter(BaseCharacter, DeltaTime, &Force, &Friction);
            }
            SDL_PushEvent(&tempEvent);
            break;
        case JUMPING_LEFT:
            Force.set(&Force, -2.0, JUMP_FORCE);
            for (uint32_t timer = 0; timer < JUMP_FRAMES; timer++) {
                moveCharacter(BaseCharacter, DeltaTime, &Force, &Friction);
                setHorrizFlip(getBaseObj(BaseCharacter), TRUE);
                DrawCharacter(SDL_SCANCODE_UP, DeltaTime, BaseCharacter, GfxRenderer, Texture);
            }
            SDL_PushEvent(&tempEvent);
            break;
        case JUMPING_RIGHT:
            Force.set(&Force, 2.0, JUMP_FORCE);
            for (uint32_t timer = 0; timer < JUMP_FRAMES; timer++) {
                setHorrizFlip(getBaseObj(BaseCharacter), FALSE);
                moveCharacter(BaseCharacter, DeltaTime, &Force, &Friction);
                DrawCharacter(SDL_SCANCODE_UP, DeltaTime, BaseCharacter, GfxRenderer, Texture);
            }
            SDL_PushEvent(&tempEvent);
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
            setHorrizFlip(getBaseObj(BaseCharacter), TRUE);
            moveCharacter(BaseCharacter, DeltaTime, &Force, &Friction);
            DrawCharacter(SDL_SCANCODE_DOWN, DeltaTime, BaseCharacter, GfxRenderer, Texture);
            break;
        case CRAWLING_RIGHT:
            Force.set(&Force, 1.0, 0.0);
            setHorrizFlip(getBaseObj(BaseCharacter), FALSE);
            moveCharacter(BaseCharacter, DeltaTime, &Force, &Friction);
            DrawCharacter(SDL_SCANCODE_DOWN, DeltaTime, BaseCharacter, GfxRenderer, Texture);
            break;
        case DEAD:
            //FIXME Play once only and quit
            Force.set(&Force,0.0, -1.3);
            moveCharacter(BaseCharacter, DeltaTime, &Force, &Friction);
            DrawCharacter(DEAD, DeltaTime,BaseCharacter, GfxRenderer, Texture);
            if (TimeInterval == 58){
                *isRunning = FALSE;
                SDL_RenderClear(*GfxRenderer);
            }
            else {
                TimeInterval++;
            }
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