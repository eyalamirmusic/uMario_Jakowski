#include "Spring.h"
#include "Common/Core.h"

Spring::Spring(int iXPos, int iYPos)
{
    this->fXPos = (float) iXPos;
    this->fYPos = (float) iYPos + 2;

    this->iHitBoxX = 32;
    this->iHitBoxY = 72;

    this->iBlockID =
        CCore::getMap()->getLevelType() == 0 || CCore::getMap()->getLevelType() == 4
            ? 37
            : 40;

    this->minionState = 0;
    this->nextFrameID = 4;
    this->inAnimation = false;
}

void Spring::Update()
{
    if (inAnimation)
    {
        Player* player = CCore::getMap()->getPlayer();

        if (getCFG().keySpace)
        {
            extraJump = true;
            player->resetJump();
            player->setNextFallFrameID(16);
        }
        else
        {
            player->stopMove();
        }

        player->setMarioSpriteID(5);

        if (nextFrameID <= 0)
        {
            switch (minionState)
            {
                case 0:
                    iBlockID = iBlockID == 37 ? 38 : 41;
                    minionState = 1;
                    player->setYPos(player->getYPos() + 16.0f);
                    break;
                case 1:
                    iBlockID = iBlockID == 38 ? 39 : 42;
                    minionState = 2;
                    player->setYPos(player->getYPos() + 16.0f);
                    break;
                case 2:
                    iBlockID = iBlockID == 39 ? 38 : 41;
                    minionState = 3;
                    player->setYPos(player->getYPos() - 16.0f);
                    break;
                case 3:
                    iBlockID = iBlockID == 38 ? 37 : 40;
                    minionState = 0;
                    player->setYPos(player->getYPos() - 16.0f);
                    player->resetJump();
                    player->startJump(4 + (extraJump ? 5 : 0));
                    player->setSpringJump(true);
                    player->startMove();
                    if (extraJump)
                        player->setCurrentJumpSpeed(10.5f);
                    inAnimation = false;
                    break;
            }
            nextFrameID = 4;
        }
        else
        {
            --nextFrameID;
        }
    }
}

void Spring::Draw(SDL_Renderer* rR, CIMG* iIMG)
{
    iIMG->draw(
        rR, (int) fXPos + (int) CCore::getMap()->getXPos(), (int) fYPos, false);
}

void Spring::collisionWithPlayer(bool TOP)
{
    if (!inAnimation)
    {
        if (TOP && CCore::getMap()->getPlayer()->getJumpState() == 2)
        {
            CCore::getMap()->getPlayer()->stopMove();
            CCore::getMap()->getPlayer()->resetJump();
            CCore::getMap()->getPlayer()->setNextFallFrameID(16);
            inAnimation = true;
            extraJump = false;
            getCFG().keySpace = false;
        }
        else
        {
            if (CCore::getMap()->getPlayer()->getMoveDirection())
            {
                CCore::getMap()->getPlayer()->setXPos(
                    (float) CCore::getMap()->getPlayer()->getXPos()
                    - CCore::getMap()->getPlayer()->getMoveSpeed());
            }
            else
            {
                CCore::getMap()->getPlayer()->setXPos(
                    (float) CCore::getMap()->getPlayer()->getXPos()
                    + CCore::getMap()->getPlayer()->getMoveSpeed());
            }
        }
    }
}
