#include "Flower.h"
#include "Common/Core.h"

Flower::Flower(int iXPos, int fYPos, int iX, int iY)
{
    this->fXPos = (float) iXPos;
    this->fYPos = (float) fYPos;

    this->iBlockID = 6;
    this->moveSpeed = 2;
    this->inSpawnState = true;
    this->minionSpawned = true;
    this->inSpawnY = 32;
    this->moveDirection = false;
    this->collisionOnlyWithPlayer = true;

    this->iX = iX;
    this->iY = iY;
}

void Flower::update()
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
}

bool Flower::updateMinion()
{
    return minionSpawned;
}

void Flower::draw(SDL_Renderer* rR, CIMG* iIMG)
{
    if (minionState >= 0)
    {
        auto map = CCore::getMap();
        iIMG->draw(rR, (int) fXPos + (int) map->getXPos(), (int) fYPos + 2, false);

        if (inSpawnState)
        {
            map->getBlock(map->getLevelType() == 0 || map->getLevelType() == 4 ? 9
                                                                               : 56)
                ->getSprite()
                ->getTexture()
                ->draw(rR,
                       (int) fXPos + (int) map->getXPos(),
                       (int) fYPos + (32 - inSpawnY)
                           - map->getMapBlock(iX, iY)->getYPos() + 2,
                       false);
        }
    }
}

void Flower::collisionWithPlayer(bool TOP)
{
    if (!inSpawnState && minionState >= 0)
    {
        CCore::getMap()->getPlayer()->setPowerLVL(
            CCore::getMap()->getPlayer()->getPowerLVL() + 1);
        minionState = -1;
    }
}
