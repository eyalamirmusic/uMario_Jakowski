#include "Hammer.h"
#include "Common/Core.h"

Hammer::Hammer(int iXPos, int iYPos, bool moveDirection)
{
    this->fXPos = (float) iXPos + 4;
    this->fYPos = (float) iYPos + 4;

    this->iBlockID =
        CCore::getMap()->getLevelType() == 0 || CCore::getMap()->getLevelType() == 4
            ? 47
            : 48;

    this->iHitBoxX = 24;
    this->iHitBoxY = 24;

    this->moveDirection = moveDirection;
    this->jumpState = MinionJump::Jump;
    this->jumpDistance = 48;
    this->currentJumpDistance = 0;
    this->moveSpeed = 0;
    this->minionState = 0;

    this->collisionOnlyWithPlayer = true;

    this->minionSpawned = true;
}

void Hammer::update()
{
    if (minionState != -2)
    {
        ++moveSpeed;
        if (moveSpeed > 35)
        {
            fXPos += moveDirection ? 3 : -3;
        }
        else if (moveSpeed > 15)
        {
            fXPos += moveDirection ? 2.5f : -2.5f;
        }
        else
        {
            fXPos += moveDirection ? 2 : -2;
        }
    }
    else
    {
        Minion::minionDeathAnimation();
    }
}

void Hammer::draw(SDL_Renderer* rR, CIMG* iIMG)
{
    if (minionState != -2)
    {
        iIMG->draw(rR,
                   (int) fXPos + (int) CCore::getMap()->getXPos() - 4,
                   (int) fYPos - 4,
                   false);
    }
    else
    {
        iIMG->drawVert(
            rR, (int) fXPos + (int) CCore::getMap()->getXPos() - 4, (int) fYPos - 4);
    }
}

void Hammer::minionPhysics()
{
    if (jumpState == MinionJump::Jump)
        Minion::jumpPhysics();
    else
    {
        currentFallingSpeed *= 1.06f;

        if (currentFallingSpeed > startJumpSpeed)
        {
            currentFallingSpeed = startJumpSpeed;
        }

        fYPos += currentFallingSpeed;

        if (fYPos >= getCFG().GAME_HEIGHT)
        {
            minionState = -1;
        }
    }
}

void Hammer::collisionWithPlayer(bool TOP)
{
    if (CCore::getMap()->getPlayer()->getStarEffect())
        setMinionState(-2);
    else
        CCore::getMap()->playerDeath(true, false);
}