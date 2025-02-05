#include "Block.h"

Block::Block(int iBlockID,
             Sprite* sSprite,
             bool bCollision,
             bool bDeath,
             bool bUse,
             bool bVisible)
{
    this->iBlockID = iBlockID;
    this->sSprite = sSprite;
    this->bCollision = bCollision;
    this->bDeath = bDeath;
    this->bUse = bUse;
    this->bVisible = bVisible;
}

void Block::draw(SDL_Renderer* rR, int iOffsetX, int iOffsetY)
{
    sSprite->getTexture()->draw(rR, iOffsetX, iOffsetY);
}

int Block::getBlockID()
{
    return iBlockID;
}

void Block::setBlockID(int iBlockID)
{
    this->iBlockID = iBlockID;
}

Sprite* Block::getSprite()
{
    return sSprite;
}

bool Block::getCollision()
{
    return bCollision;
}

bool Block::getDeath()
{
    return bDeath;
}

bool Block::getUse()
{
    return bUse;
}

bool Block::getVisible()
{
    return bVisible;
}