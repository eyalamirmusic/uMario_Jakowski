#include "Fire.h"
#include "Common/Core.h"

Fire::Fire(float fXPos, float fYPos, int toYPos)
{
    this->fXPos = fXPos;
    this->fYPos = fYPos;
    this->toYPos = toYPos;

    this->collisionOnlyWithPlayer = true;

    this->moveDirection = true;

    this->iBlockID = 22;
    this->iHitBoxX = 48;
    this->iHitBoxY = 10;

    this->minionSpawned = true;
}

void Fire::update()
{
    fXPos -= 2;

    if (fXPos + iHitBoxX < 0)
    {
        minionState = -1;
    }

    if (toYPos > fYPos)
    {
        ++fYPos;
    }
    else if (toYPos < fYPos)
    {
        --fYPos;
    }
}

void Fire::draw(SDL_Renderer* rR, CIMG* iIMG)
{
    iIMG->draw(rR, (int) (fXPos + CCore::getMap()->getXPos()), (int) fYPos - 4);
}

void Fire::minionPhysics()
{
}

/* ******************************************** */

void Fire::collisionWithPlayer(bool TOP)
{
    CCore::getMap()->playerDeath(true, false);
}