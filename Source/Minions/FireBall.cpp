#include "FireBall.h"
#include "Common/Core.h"
#include <math.h>

FireBall::FireBall(
    int iXPos, int iYPos, int radius, int nSliceID, bool moveDirection)
{
    this->iCenterX = iXPos;
    this->iCenterY = iYPos;

    this->iHitBoxX = 16;
    this->iHitBoxY = 16;

    this->radius = radius;

    this->moveDirection = moveDirection;
    this->collisionOnlyWithPlayer = true;

    this->minionSpawned = true;

    this->slice = 2 * M_PI / 360;
    this->sliceID = nSliceID;
    this->angle = slice * sliceID;

    this->fXPos = (float) (iXPos + radius * cos(angle));
    this->fYPos = (float) (iYPos + radius * sin(angle));

    this->iBlockID = 23;
}

void FireBall::update()
{
    if (moveDirection)
    {
        this->angle = slice * sliceID;

        this->fXPos = (float) (iCenterX + radius * cos(angle));
        this->fYPos = (float) (iCenterY + radius * sin(angle));

        if (sliceID <= 0)
        {
            sliceID = 360;
        }
        else
        {
            sliceID -= 2;
        }
    }
    else
    {
        this->angle = slice * sliceID;

        this->fXPos = (float) (iCenterX + radius * cos(angle));
        this->fYPos = (float) (iCenterY + radius * sin(angle));

        if (sliceID > 359)
        {
            sliceID = 0;
        }
        else
        {
            sliceID += 2;
        }
    }
}

void FireBall::draw(SDL_Renderer* rR, CIMG* iIMG)
{
    iIMG->draw(rR, (int) (fXPos + CCore::getMap()->getXPos()), (int) fYPos);
}

void FireBall::collisionWithPlayer(bool TOP)
{
    CCore::getMap()->playerDeath(true, false);
}