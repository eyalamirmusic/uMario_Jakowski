#include "CheepSpawner.h"
#include "Common/Core.h"
#include "stdlib.h"
#include "time.h"

/* ******************************************** */

CheepSpawner::CheepSpawner(int iXPos, int iXEnd)
{
    this->fXPos = (float) iXPos;
    this->fYPos = 0;
    this->iXEnd = iXEnd;

    this->collisionOnlyWithPlayer = true;
    this->iHitBoxX = this->iHitBoxY = 1;

    this->minionSpawned = true;

    nextCheep();

    this->iBlockID = 0;

    srand((unsigned) time(nullptr));
}

void CheepSpawner::update()
{
    if (iSpawnTime < SDL_GetTicks())
    {
        spawnCheep();
        nextCheep();
    }
}

void CheepSpawner::minionPhysics()
{
}

/* ******************************************** */

void CheepSpawner::spawnCheep()
{
    if (CCore::getMap()->getPlayer()->getXPos() - CCore::getMap()->getXPos() > fXPos
        && CCore::getMap()->getPlayer()->getXPos() - CCore::getMap()->getXPos()
               < iXEnd)
    {
        CCore::getMap()->addCheep((int) (-CCore::getMap()->getXPos() + 64
                                         + rand() % (getCFG().GAME_WIDTH - 128)),
                                  getCFG().GAME_HEIGHT - 4,
                                  2,
                                  2 + rand() % 32,
                                  !(rand() % 4 == 0));
    }
    else
    {
        nextCheep();
    }
}

void CheepSpawner::nextCheep()
{
    iSpawnTime = SDL_GetTicks() + 675 + rand() % 1025;
}