#include "BulletBillSpawner.h"
#include "Common/Core.h"
#include <cstdlib>
#include <ctime>

BulletBillSpawner::BulletBillSpawner(int iXPos, int iYPos, int minionState)
{
    this->fXPos = (float) iXPos;
    this->fYPos = (float) iYPos;

    this->moveSpeed = 0;

    this->collisionOnlyWithPlayer = true;

    this->minionState = minionState;

    this->iBlockID = 0;
    this->minionSpawned = minionState != 0;

    srand((unsigned) time(NULL));
}

void BulletBillSpawner::update()
{
    auto map = CCore::getMap();
    auto player = map->getPlayer();

    if (nextBulletBillFrameID <= 0)
    {
        if (minionState == 0)
        {
            if (fXPos > -map->getXPos() - 64
                && fXPos < -map->getXPos() + getCFG().GAME_WIDTH + 64 + iHitBoxX)
            {
                if (!(player->getXPos() - map->getXPos() + player->getHitBoxX() / 2
                          > fXPos - 96
                      && player->getXPos() - map->getXPos()
                                 + player->getHitBoxX() / 2
                             < fXPos + 96))
                {
                    map->addBulletBill(
                        (int) fXPos, (int) fYPos - 14, true, minionState);
                    nextBulletBillFrameID = 145 + rand() % 145;
                }
            }
        }
        else
        {
            map->addBulletBill(
                (int) (-map->getXPos() + getCFG().GAME_WIDTH + iHitBoxX * 2),
                (int) fYPos - rand() % 9 * 32 - 16,
                true,
                minionState);
            nextBulletBillFrameID = 80 + rand() % 96;
        }
    }
    else
    {
        if (!(player->getXPos() - map->getXPos() + player->getHitBoxX() / 2
                  > fXPos - 96
              && player->getXPos() - map->getXPos() + player->getHitBoxX() / 2
                     < fXPos + 96))
        {
            --nextBulletBillFrameID;
        }
    }
}
