#include "Toad.h"
#include "Common/Core.h"


Toad::Toad(int iXPos, int iYPos, bool peach)
{
    this->fXPos = (float) iXPos;
    this->fYPos = (float) iYPos;

    this->moveSpeed = 0;
    this->collisionOnlyWithPlayer = true;

    this->minionSpawned = true;
    this->iBlockID = peach ? 27 : 26;

    this->iHitBoxX = 32;
    this->iHitBoxY = 48;
}

void Toad::draw(SDL_Renderer* rR, CIMG* iIMG)
{
    iIMG->draw(
        rR, (int) (fXPos + CCore::getMap()->getXPos()), (int) fYPos, !moveDirection);
}
