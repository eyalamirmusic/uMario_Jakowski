#pragma once

#include "Graphics/IMG.h"
#include "Graphics/Sprite.h"

class Block
{
public:
    Block(int iBlockID,
          Sprite* sSprite,
          bool bCollision,
          bool bDeath,
          bool bUse,
          bool bVisible);

    void draw(SDL_Renderer* rR, int iOffsetX, int iOffsetY);

    /* ----- get & set ----- */
    int getBlockID();
    void setBlockID(int iID);

    Sprite* getSprite();
    bool getCollision();
    bool getDeath();
    bool getUse();
    bool getVisible();

private:
    EA::OwningPointer<Sprite> sSprite;

    int iBlockID;

    bool bCollision;
    bool bDeath;
    bool bUse;
    bool bVisible;
};