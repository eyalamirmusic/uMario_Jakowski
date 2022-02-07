#include "Star.h"
#include "Common/Core.h"

Star::Star(int iXPos, int iYPos, int iX, int iY)
{
    this->fXPos = (float) iXPos + 2;
    this->fYPos = (float) iYPos;

    this->collisionOnlyWithPlayer = true;

    this->moveDirection = false;
    this->moveSpeed = 3;

    this->inSpawnState = true;
    this->minionSpawned = true;
    this->inSpawnY = 30;
    this->startJumpSpeed = 4;

    this->iX = iX;
    this->iY = iY;

    this->iBlockID = 24;

    this->iHitBoxX = 28;
    this->iHitBoxY = 32;
}

void Star::update()
{
    if (inSpawnState)
    {
        if (inSpawnY <= 0)
        {
            inSpawnState = false;
        }
        else
        {
            if (fYPos > -5)
            {
                inSpawnY -= 2;
                fYPos -= 2;
            }
            else
            {
                inSpawnY -= 1;
                fYPos -= 1;
            }
        }
    }
    else
    {
        if (jumpState == MinionJump::None)
        {
            startJump(1);
            jumpDistance = 32;
        }
        updateXPos();
    }
}

bool Star::updateMinion()
{
    if (!inSpawnState)
    {
        minionPhysics();
    }

    return minionSpawned;
}

void Star::minionPhysics()
{
    if (jumpState == MinionJump::Jump)
    {
        if (minionState == 0)
        {
            updateYPos(-4 + (currentJumpDistance > 64 ? 2 : 0));
            currentJumpDistance += 2;

            if (jumpDistance <= currentJumpDistance)
            {
                jumpState = MinionJump::Land;
            }
        }
    }
    else
    {
        if (!CCore::getMap()->checkCollisionLB(
                (int) fXPos + 2, (int) fYPos + 2, iHitBoxY, true)
            && !CCore::getMap()->checkCollisionRB(
                (int) fXPos - 2, (int) fYPos + 2, iHitBoxX, iHitBoxY, true))
        {
            Minion::physicsLand();
        }
        else
        {
            jumpState = MinionJump::None;
        }
    }
}

void Star::draw(SDL_Renderer* rR, CIMG* iIMG)
{
    iIMG->draw(
        rR, (int) fXPos + (int) CCore::getMap()->getXPos(), (int) fYPos + 2, false);
    if (inSpawnState)
    {
        CCore::getMap()
            ->getBlock(CCore::getMap()->getLevelType() == 0
                               || CCore::getMap()->getLevelType() == 4
                           ? 9
                           : 56)
            ->getSprite()
            ->getTexture()
            ->draw(rR,
                   (int) fXPos + (int) CCore::getMap()->getXPos() - 2,
                   (int) fYPos + (32 - inSpawnY)
                       - CCore::getMap()->getMapBlock(iX, iY)->getYPos(),
                   false);
    }
}

void Star::collisionWithPlayer(bool TOP)
{
    if (!inSpawnState)
    {
        CCore::getMap()->getPlayer()->setStarEffect(true);
        minionState = -1;
    }
}