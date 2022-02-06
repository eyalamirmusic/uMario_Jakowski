#include "Spikey.h"
#include "Common/Core.h"

Spikey::Spikey(int iXPos, int iYPos)
{
    this->fXPos = (float) iXPos;
    this->fYPos = (float) iYPos + 6;

    this->iHitBoxX = 32;
    this->iHitBoxY = 26;

    this->iBlockID = 52;

    this->startJump(1);

    this->moveSpeed = 0;
}

void Spikey::Update()
{
    if (minionState == 0)
        updateXPos();
    else if (minionState == -2)
        Minion::minionDeathAnimation();
}

void Spikey::Draw(SDL_Renderer* rR, CIMG* iIMG)
{
    if (minionState != -2)
    {
        iIMG->draw(rR,
                   (int) fXPos + (int) CCore::getMap()->getXPos(),
                   (int) fYPos - 4,
                   !moveDirection);
    }
    else
    {
        iIMG->drawVert(
            rR, (int) fXPos + (int) CCore::getMap()->getXPos(), (int) fYPos + 2);
    }
}

void Spikey::minionPhysics()
{
    if (jumpState == 1)
    {
        physicsState1();
    }
    else
    {
        auto map = CCore::getMap();

        if (!map->checkCollisionLB((int) fXPos + 2, (int) fYPos + 2, iHitBoxY, true)
            && !map->checkCollisionRB(
                (int) fXPos - 2, (int) fYPos + 2, iHitBoxX, iHitBoxY, true)
            && !onAnotherMinion)
        {
            physicsState2();
        }
        else
        {
            jumpState = 0;
            onAnotherMinion = false;

            if (iBlockID == 52)
            {
                iBlockID = 51;
                auto player = map->getPlayer();

                moveDirection =
                    fXPos + iHitBoxX / 2
                    > player->getXPos() - map->getXPos() + player->getHitBoxX() / 2;
                moveSpeed = 1;
            }
        }
    }
}

void Spikey::collisionWithPlayer(bool TOP)
{
    if (CCore::getMap()->getPlayer()->getStarEffect())
    {
        setMinionState(-2);
    }
    else
    {
        CCore::getMap()->playerDeath(true, false);
    }
}