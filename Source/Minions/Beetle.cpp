#include "Beetle.h"
#include "Common/Core.h"

Beetle::Beetle(int iXPos, int iYPos, bool moveDirection)
{
    this->fXPos = (float) iXPos;
    this->fYPos = (float) iYPos;

    this->minionState = 0;
    this->iBlockID =
        CCore::getMap()->getLevelType() == 0 || CCore::getMap()->getLevelType() == 4
            ? 53
        : CCore::getMap()->getLevelType() == 1 ? 55
                                               : 57;
    this->moveDirection = moveDirection;
    this->moveSpeed = 1;
}

void Beetle::update()
{
    if (minionState == -2)
        Minion::minionDeathAnimation();
    else
        updateXPos();
}

void Beetle::draw(SDL_Renderer* rR, CIMG* iIMG)
{
    if (minionState != -2)
    {
        iIMG->draw(rR,
                   (int) fXPos + (int) CCore::getMap()->getXPos(),
                   (int) fYPos,
                   !moveDirection);
    }
    else
    {
        iIMG->drawVert(
            rR, (int) fXPos + (int) CCore::getMap()->getXPos(), (int) fYPos);
    }
}

void Beetle::collisionWithPlayer(bool TOP)
{
    auto player = CCore::getMap()->getPlayer();

    if (player->getStarEffect())
        setMinionState(-2);
    else if (TOP)
    {
        if (minionState == 0)
        {
            minionState = 1;

            ++iBlockID;
            player->resetJump();
            player->startJump(1);
            player->setYPos((float) player->getYPos() - 4);
            points(100);
            getCFG().getMusic()->playEffect(Mario::Music::Effects::Stomp);
            moveSpeed = 0;
            killOtherUnits = true;
        }
        else
        {
            if (moveSpeed > 0)
            {
                moveSpeed = 0;
            }
            else
            {
                if ((fXPos + iHitBoxX) / 2
                    < (player->getXPos() - CCore::getMap()->getXPos()
                       + player->getHitBoxX())
                          / 2)
                {
                    moveDirection = true;
                }
                else
                {
                    moveDirection = false;
                }

                moveSpeed = 6;
            }

            player->setYPos((float) player->getYPos() - 4);
            player->resetJump();
            player->startJump(1);
            points(100);
            getCFG().getMusic()->playEffect(Mario::Music::Effects::Stomp);
        }
    }
    else
    {
        if (minionState == 1)
        {
            if (moveSpeed == 0)
            {
                //moveDirection = !CCore::getMap()->getPlayer()->getMoveDirection();
                moveDirection = (fXPos + iHitBoxX / 2
                                 < player->getXPos() - CCore::getMap()->getXPos()
                                       + player->getHitBoxX() / 2);
                if (moveDirection)
                    fXPos -= player->getMoveSpeed() + 1;
                else
                    fXPos += player->getMoveSpeed() + 1;
                moveSpeed = 6;
                getCFG().getMusic()->playEffect(Mario::Music::Effects::Stomp);
            }
            else
            {
                CCore::getMap()->playerDeath(true, false);
            }
        }
        else
        {
            CCore::getMap()->playerDeath(true, false);
        }
    }
}

void Beetle::collisionEffect()
{
    if (minionState == 0)
        moveDirection = !moveDirection;
}

void Beetle::setMinionState(int minionState)
{
    if (minionState != -2 || CCore::getMap()->getPlayer()->getStarEffect())
        Minion::setMinionState(minionState);
    else
        moveDirection = !moveDirection;
}