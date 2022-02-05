#include "Vine.h"
#include "Common/Core.h"

/* ******************************************** */

Vine::Vine(int iXPos, int iYPos, int minionState, int iBlockID)
{
    this->fXPos = (float) iXPos * 32 + 4;
    this->fYPos = (float) (CCFG::GAME_HEIGHT - 16 - iYPos * 32);

    this->iX = iXPos;
    this->iY = iYPos;

    this->minionState = minionState;
    this->iBlockID = iBlockID;

    this->moveSpeed = 0;

    this->collisionOnlyWithPlayer = true;

    this->jumpDistance = 0;
    this->minionSpawned = true;

    this->iHitBoxX = 24;
    this->iHitBoxY = -32;
}

Vine::~Vine(void)
{
}

/* ******************************************** */

void Vine::Update()
{
    if (minionState == 0)
    {
        if (CCFG::GAME_HEIGHT + 16 - iY * 32 >= jumpDistance)
        {
            jumpDistance += 2;
            iHitBoxY += 2;
            fYPos -= 2;
        }
    }
    else
    {
        if (jumpDistance < 256)
        {
            jumpDistance += 2;
            iHitBoxY += 2;
            fYPos -= 2;
        }
    }
}

void Vine::Draw(SDL_Renderer* rR, CIMG* iIMG)
{
    if (jumpDistance < 32)
    {
        CCore::getMap()
            ->getMinionBlock(iBlockID - 1)
            ->Draw(rR,
                   (int) (iX * 32 + CCore::getMap()->getXPos()),
                   (int) (CCFG::GAME_HEIGHT - 16 - iY * 32 - jumpDistance));
    }
    else
    {
        CCore::getMap()
            ->getMinionBlock(iBlockID - 1)
            ->Draw(rR,
                   (int) (iX * 32 + CCore::getMap()->getXPos()),
                   (int) (CCFG::GAME_HEIGHT - 16 - iY * 32 - jumpDistance));
        for (int i = 0; i < jumpDistance / 32 - 1; i++)
        {
            iIMG->Draw(
                rR,
                (int) (iX * 32 + CCore::getMap()->getXPos()),
                (int) (CCFG::GAME_HEIGHT + 16 - iY * 32 + i * 32 - jumpDistance),
                false);
        }
    }
    CCore::getMap()
        ->getBlock(CCore::getMap()->getMapBlock((int) iX, (int) iY)->getBlockID())
        ->getSprite()
        ->getTexture()
        ->Draw(
            rR,
            (int) (iX * 32 + CCore::getMap()->getXPos()),
            (int) (CCFG::GAME_HEIGHT - iY * 32 - 16
                   - CCore::getMap()->getMapBlock((int) iX, (int) iY)->getYPos()));
}

void Vine::minionPhysics()
{
}

/* ******************************************** */

void Vine::collisionWithPlayer(bool TOP)
{
    if (minionState == 0)
    {
        auto* map = CCore::getMap();
        map->setInEvent(true);

        auto* event = map->getEvent();
        event->resetData();
        map->getPlayer()->resetJump();
        map->getPlayer()->stopMove();

        event->eventTypeID = Mario::EventType::Normal;

        event->iSpeed = 2;

        event->newLevelType = map->getLevelType();
        event->newCurrentLevel = map->getCurrentLevelID();
        event->newMoveMap = true;
        event->iDelay = 0;
        event->inEvent = false;

        event->newMoveMap = true;
        event->newUnderWater = false;

        if (fXPos + iHitBoxX / 2
            > map->getPlayer()->getXPos() - map->getXPos())
        {
            event->vOLDDir.push_back(
                Mario::Animations::Right);
            event->vOLDLength.push_back(map->getPlayer()->getHitBoxX() - 4);
        }
        else
        {
            event->vOLDDir.push_back(
                Mario::Animations::Left);
            event->vOLDLength.push_back(map->getPlayer()->getHitBoxX() - 4);
        }

        for (int i = 0; i < map->getPlayer()->getYPos()
                                + map->getPlayer()->getHitBoxY();
             i += 32)
        {
            event->vOLDDir.push_back(
                Mario::Animations::Vine1);
            event->vOLDLength.push_back(16);
            event->vOLDDir.push_back(
                Mario::Animations::Vine2);
            event->vOLDLength.push_back(16);
        }

        switch (map->getCurrentLevelID())
        {
            case 4:
            {
                event->newMapXPos = -270 * 32;
                event->newPlayerXPos = 128;
                event->newPlayerYPos =
                    CCFG::GAME_HEIGHT - map->getPlayer()->getHitBoxY();
                event->vOLDDir.push_back(
                    Mario::Animations::VineSpawn);
                event->vOLDLength.push_back(274);

                break;
            }
            case 8:
            {
                event->newMapXPos = -270 * 32;
                event->newPlayerXPos = 128;
                event->newPlayerYPos =
                    CCFG::GAME_HEIGHT - map->getPlayer()->getHitBoxY();
                event->vOLDDir.push_back(
                    Mario::Animations::VineSpawn);
                event->vOLDLength.push_back(274);

                break;
            }
            case 13:
            {
                event->newMapXPos = -310 * 32;
                event->newPlayerXPos = 128;
                event->newPlayerYPos =
                    CCFG::GAME_HEIGHT - map->getPlayer()->getHitBoxY();
                event->newLevelType = 0;

                event->vOLDDir.push_back(
                    Mario::Animations::VineSpawn);
                event->vOLDLength.push_back(314);
                break;
            }
            case 17:
            {
                event->newMapXPos = -325 * 32;
                event->newPlayerXPos = 128;
                event->newPlayerYPos =
                    CCFG::GAME_HEIGHT - map->getPlayer()->getHitBoxY();
                event->newLevelType = 0;

                event->vOLDDir.push_back(
                    Mario::Animations::VineSpawn);
                event->vOLDLength.push_back(329);
                break;
            }
            case 21:
            {
                event->newMapXPos = -390 * 32;
                event->newPlayerXPos = 128;
                event->newPlayerYPos =
                    CCFG::GAME_HEIGHT - map->getPlayer()->getHitBoxY();
                event->newLevelType = 4;

                event->vOLDDir.push_back(
                    Mario::Animations::VineSpawn);
                event->vOLDLength.push_back(394);
                break;
            }
        }

        event->vOLDDir.push_back(
            Mario::Animations::Nothing);
        event->vOLDLength.push_back(60);

        for (int i = 0; i < 64; i += 32)
        {
            event->vNEWDir.push_back(
                Mario::Animations::Vine1);
            event->vNEWLength.push_back(16);
            event->vNEWDir.push_back(
                Mario::Animations::Vine2);
            event->vNEWLength.push_back(16);
        }
    }
    else {}
}