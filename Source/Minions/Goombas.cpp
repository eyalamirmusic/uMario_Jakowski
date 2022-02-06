#include "Goombas.h"
#include "Common/Core.h"

Goombas::Goombas(int iX, int iY, int iBlockID, bool moveDirection)
{
    this->fXPos = (float) iX;
    this->fYPos = (float) iY;
    this->iBlockID = iBlockID;
    this->moveDirection = moveDirection;
    this->moveSpeed = 1;
}

void Goombas::update()
{
    if (minionState == 0)
    {
        updateXPos();
    }
    else if (minionState == -2)
    {
        Minion::minionDeathAnimation();
    }
    else if (SDL_GetTicks() - 500 >= (unsigned) deadTime)
    {
        minionState = -1;
    }
}

void Goombas::draw(SDL_Renderer* rR, CIMG* iIMG)
{
    if (minionState != -2)
    {
        iIMG->draw(rR,
                   (int) fXPos + (int) CCore::getMap()->getXPos(),
                   (int) fYPos + 2,
                   false);
    }
    else
    {
        iIMG->drawVert(
            rR, (int) fXPos + (int) CCore::getMap()->getXPos(), (int) fYPos + 2);
    }
}

void Goombas::collisionWithPlayer(bool TOP)
{
    auto player = CCore::getMap()->getPlayer();

    if (player->getStarEffect())
    {
        setMinionState(-2);
    }
    else if (TOP)
    {
        if (minionState == 0)
        {
            minionState = 1;
            int levelType = CCore::getMap()->getLevelType();

            iBlockID = levelType == 0 || levelType == 4 ? 1
                       : levelType == 1                 ? 9
                                                        : 11;
            deadTime = SDL_GetTicks();
            player->resetJump();
            player->startJump(1);
            points(100);
            getCFG().getMusic()->playEffect(Mario::Music::Effects::Stomp);
        }
    }
    else
    {
        CCore::getMap()->playerDeath(true, false);
    }
}

void Goombas::setMinionState(int minionState)
{
    this->minionState = minionState;

    if (this->minionState == 1)
        deadTime = (int) SDL_GetTicks();

    Minion::setMinionState(minionState);
}