#include "Pipe.h"
#include "Common/Core.h"

/* ******************************************** */

Pipe::Pipe(int iType,
           int iLX,
           int iLY,
           int iRX,
           int iRY,
           int newPlayerPosX,
           int newPlayerPosY,
           int newCurrentLevel,
           int newLevelType,
           bool newMoveMap,
           int iDelay,
           int iSpeed,
           bool newUnderWater)
{
    this->iType = iType;

    this->iLX = iLX;
    this->iLY = iLY;
    this->iRX = iRX;
    this->iRY = iRY;

    this->newPlayerPosX = newPlayerPosX;
    this->newPlayerPosY = newPlayerPosY;

    this->newCurrentLevel = newCurrentLevel;
    this->newLevelType = newLevelType;
    this->newMoveMap = newMoveMap;
    this->newUnderWater = newUnderWater;

    this->iDelay = iDelay;

    this->iSpeed = iSpeed;
}

Pipe::~Pipe(void)
{
}

/* ******************************************** */

void Pipe::checkUse()
{
    if (iType == 0 || iType == 2)
    {
        if (CCore::getMap()->getPlayer()->getSquat()
            && -(int) CCore::getMap()->getXPos()
                       + CCore::getMap()->getPlayer()->getXPos()
                   >= iLX * 32 + 4
            && -(int) CCore::getMap()->getXPos()
                       + CCore::getMap()->getPlayer()->getXPos()
                       + CCore::getMap()->getPlayer()->getHitBoxX()
                   < (iRX + 1) * 32 - 4)
        {
            setEvent();
        }
    }
    else
    {
        if (!CCore::getMap()->getPlayer()->getSquat()
            && CCore::getMap()->getBlockIDX(
                   -(int) CCore::getMap()->getXPos()
                   + CCore::getMap()->getPlayer()->getXPos()
                   + CCore::getMap()->getPlayer()->getHitBoxX() / 2 + 2)
                   == iRX - 1
            && CCore::getMap()->getBlockIDY(
                   CCore::getMap()->getPlayer()->getYPos()
                   + CCore::getMap()->getPlayer()->getHitBoxY() + 2)
                   == iRY - 1)
        {
            setEvent();
        }
    }
}

/* ******************************************** */

void Pipe::setEvent()
{
    auto* map = CCore::getMap();
    auto* event = map->getEvent();
    
    event->resetData();
    auto* player = map->getPlayer();
    player->stopMove();
    player->resetJump();

    CCFG::getMusic()->playEffect(Mario::Music::Effects::Pipe);

    event->eventTypeID = Mario::Event::eventType::eNormal;

    event->newCurrentLevel = newCurrentLevel;
    event->newLevelType = newLevelType;
    event->newMoveMap = newMoveMap;

    event->iSpeed = iSpeed;
    event->iDelay = iDelay;

    event->inEvent = false;

    event->newUnderWater = newUnderWater;

    event->newMapXPos = (newPlayerPosX <= 32 * 2 ? 0 : -(newPlayerPosX - 32 * 2));
    event->newPlayerXPos = (newPlayerPosX <= 32 * 2 ? newPlayerPosX : 32 * 2);
    event->newPlayerYPos = newPlayerPosY;

    if (iType == 0)
    { // VERTICAL -> NONE
        event->newPlayerYPos -= player->getPowerLVL() > 0 ? 32 : 0;
        event->vOLDDir.push_back(Mario::Animations::eBOT);
        event->vOLDLength.push_back(player->getHitBoxY());

        event->vOLDDir.push_back(Mario::Animations::eNOTHING);
        event->vOLDLength.push_back(35);

        for (int i = 0; i < 3; i++)
        {
            event->reDrawX.push_back(iLX);
            event->reDrawY.push_back(iLY - i);
            event->reDrawX.push_back(iRX);
            event->reDrawY.push_back(iRY - i);
        }
    }
    else if (iType == 1)
    {
        event->newPlayerXPos += 32 - player->getHitBoxX() / 2;

        event->vOLDDir.push_back(Mario::Animations::eRIGHT);
        event->vOLDLength.push_back(player->getHitBoxX());

        event->vOLDDir.push_back(Mario::Animations::eNOTHING);
        event->vOLDLength.push_back(35);

        event->vNEWDir.push_back(Mario::Animations::ePLAYPIPETOP);
        event->vNEWLength.push_back(1);

        event->vNEWDir.push_back(Mario::Animations::eNOTHING);
        event->vNEWLength.push_back(35);

        event->vNEWDir.push_back(Mario::Animations::eTOP);
        event->vNEWLength.push_back(player->getHitBoxY());

        for (int i = 0; i < 3; i++)
        {
            event->reDrawX.push_back(iLX + i);
            event->reDrawY.push_back(iLY);
            event->reDrawX.push_back(iRX + i);
            event->reDrawY.push_back(iRY);

            event->reDrawX.push_back(
                map->getBlockIDX(
                event->newPlayerXPos - event->newMapXPos));
            event->reDrawY.push_back(map->getBlockIDY(newPlayerPosY) - 1
                                     - i);
            event->reDrawX.push_back(
                map->getBlockIDX(
                                         event->newPlayerXPos - event->newMapXPos)
                                     + 1);
            event->reDrawY.push_back(map->getBlockIDY(newPlayerPosY) - 1
                                     - i);
        }
    }
    else
    { // -- VERT -> VERT
        event->newPlayerXPos -=
            player->getPowerLVL() > 0
                ? 32
                : 0 - player->getHitBoxX() / 2;
        event->vOLDDir.push_back(Mario::Animations::eBOT);
        event->vOLDLength.push_back(player->getHitBoxY());

        event->vOLDDir.push_back(Mario::Animations::eNOTHING);
        event->vOLDLength.push_back(55);

        for (int i = 0; i < 3; i++)
        {
            event->reDrawX.push_back(iLX);
            event->reDrawY.push_back(iLY - i);
            event->reDrawX.push_back(iRX);
            event->reDrawY.push_back(iRY - i);

            event->reDrawX.push_back(
                map->getBlockIDX(
                event->newPlayerXPos - event->newMapXPos));
            event->reDrawY.push_back(map->getBlockIDY(newPlayerPosY) - 1
                                     - i);
            event->reDrawX.push_back(
                map->getBlockIDX(
                                         event->newPlayerXPos - event->newMapXPos)
                                     + 1);
            event->reDrawY.push_back(map->getBlockIDY(newPlayerPosY) - 1
                                     - i);
        }

        event->vNEWDir.push_back(Mario::Animations::ePLAYPIPETOP);
        event->vNEWLength.push_back(1);

        event->vNEWDir.push_back(Mario::Animations::eNOTHING);
        event->vNEWLength.push_back(35);

        event->vNEWDir.push_back(Mario::Animations::eTOP);
        event->vNEWLength.push_back(player->getHitBoxY());
    }

    map->setInEvent(true);
}