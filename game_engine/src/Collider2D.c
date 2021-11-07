//
// Created by Iordan Tonchev on 6.11.21.
//

#include <SDL.h>

#include "Physics/Collider2D.h"
#include "Graphics/Transform2D.h"

struct Collider2D {
    SDL_Rect ColliderRect;
    STRING ColliderTag;
    Transform2D *ObjTransformPtr;
    BOOL Enabled;
};

void initCollider2D(Collider2D *Collider, int32_t X, int32_t Y, int32_t W, int32_t H, int32_t Scale, STRING Tag) {
    Collider = (struct Collider2D *)malloc(sizeof (struct Collider2D));
    Collider->ColliderRect.x = X;
    Collider->ColliderRect.y = Y;
    Collider->ColliderRect.w = W * Scale;
    Collider->ColliderRect.h = H * Scale;
    Collider->Enabled = TRUE;
    Collider->ColliderTag = Tag;
}

void deinitCollider2D (Collider2D *Collider){
    free(Collider);
    Collider = NULL;
}

inline void setColliderStatus(Collider2D *Collider, BOOL NewStatus) {Collider->Enabled = NewStatus;}
inline BOOL getColliderStatus (Collider2D *Collider){ return Collider->Enabled;}

/*void ScaleCollider2D(Collider2D *Collider, int32_t Scale) {
     Collider->ColliderRect.w * Scale;
     Collider->ColliderRect.h * Scale;
}*/

