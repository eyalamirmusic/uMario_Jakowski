#include "Lakito.h"
#include "Common/Core.h"
#include <cstdlib>
#include <ctime>

Lakito::Lakito(int iXPos, int iYPos, int iMaxXPos)
{
    this->fXPos = (float) iXPos + 16;
    this->fYPos = (float) iYPos;

    this->iMaxXPos = iMaxXPos;
    this->followPlayer = false;
    this->end = false;

    this->iBlockID = 50;

    this->collisionOnlyWithPlayer = true;
    this->iHitBoxX = 32;
    this->iHitBoxY = 26;

    this->moveDirection = true;

    this->nextSpikeyFrameID = 128;

    this->minionSpawned = true;

    srand((unsigned) time(NULL));
}

void Lakito::update()
{
    if (minionState == -2)
    {
        Minion::minionDeathAnimation();
    }
    else
    {
        if (fXPos > iMaxXPos)
        {
            end = true;
        }

        if (end)
        {
            fXPos -= 1;

            if (fXPos < -iHitBoxX)
            {
                minionState = -1;
            }

            return;
        }

        auto map = CCore::getMap();
        
        if (fXPos < -map->getXPos() - 64)
            fXPos = -map->getXPos() - 32;

        auto player = map->getPlayer();

        if (fXPos <= player->getXPos()
                         - map->getXPos()
                         + player->getHitBoxX() / 2
                         + 32 * player->getMoveSpeed()
            && player->getMove()
            && player->getMoveDirection())
        {
            moveSpeed = player->getMoveSpeed()
                + (fXPos < player->getXPos()
                               - map->getXPos()
                               + player->getHitBoxX() / 2
                               + 32 * player->getMoveSpeed());
            fXPos += moveSpeed;
            followPlayer = true;
            moveDirection = true;
        }
        else
        {
            if (followPlayer)
            {
                if (moveSpeed > 0)
                {
                    fXPos += moveSpeed;
                    --moveSpeed;
                }
                else
                {
                    followPlayer = false;
                }
            }
            else
            {
                if (!moveDirection)
                {
                    fXPos -= 1;

                    if (fXPos < player->getXPos()
                                    - map->getXPos()
                                    + player->getHitBoxX() / 2
                                    - 128)
                    {
                        moveDirection = true;
                    }
                }
                else
                {
                    fXPos += 1;
                    if (fXPos > player->getXPos()
                                    - map->getXPos()
                                    + player->getHitBoxX() / 2
                                    + 128)
                    {
                        moveDirection = false;
                    }
                }
            }
        }

        if (nextSpikeyFrameID < rand() % 85)
        {
            iBlockID = 49;
        }

        if (nextSpikeyFrameID <= 0)
        {
            map->addSpikey((int) fXPos, (int) (fYPos - 32));
            nextSpikeyFrameID = 135 + rand() % 175;
            iBlockID = 50;
        }
        else
        {
            --nextSpikeyFrameID;
        }
    }
}

void Lakito::draw(SDL_Renderer* rR, CIMG* iIMG)
{
    if (minionState != -2)
    {
        iIMG->draw(rR,
                   (int) fXPos + (int) CCore::getMap()->getXPos(),
                   (int) fYPos - 16,
                   !moveDirection);
    }
    else
    {
        iIMG->drawVert(
            rR, (int) fXPos + (int) CCore::getMap()->getXPos(), (int) fYPos - 16);
    }
}

void Lakito::collisionWithPlayer(bool TOP)
{
    if (CCore::getMap()->getPlayer()->getStarEffect() || TOP)
    {
        setMinionState(-2);
    }
    else if (!end)
    {
        CCore::getMap()->playerDeath(true, false);
    }
}