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

    leftBlockPos = {iLX, iLY};
    rightBlockPos = {iRX, iRY};
    newPlayerPos = {newPlayerPosX, newPlayerPosY};

    this->newCurrentLevel = newCurrentLevel;
    this->newLevelType = newLevelType;
    this->newMoveMap = newMoveMap;
    this->newUnderWater = newUnderWater;

    this->iDelay = iDelay;

    this->iSpeed = iSpeed;
}

void Pipe::checkUse()
{
    auto* map = CCore::getMap();
    auto* player = map->getPlayer();

    int xPos = (int) map->getXPos();
    int playerX = player->getXPos();

    if (iType == 0 || iType == 2)
    {
        if (player->getSquat() && -xPos + playerX >= leftBlockPos.x * 32 + 4
            && -xPos + playerX + player->getHitBoxX()
                   < (rightBlockPos.x + 1) * 32 - 4)
        {
            setEvent();
        }
    }
    else
    {
        if (!player->getSquat()
            && map->getBlockIDX(-xPos + playerX + player->getHitBoxX() / 2 + 2)
                   == rightBlockPos.x - 1
            && map->getBlockIDY(player->getYPos() + player->getHitBoxY() + 2)
                   == rightBlockPos.y - 1)
        {
            setEvent();
        }
    }
}

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

    event->newMapXPos = (newPlayerPos.x <= 32 * 2 ? 0 : -(newPlayerPos.x - 32 * 2));
    event->newPlayerXPos = (newPlayerPos.x <= 32 * 2 ? newPlayerPos.x : 32 * 2);
    event->newPlayerYPos = newPlayerPos.y;

    if (iType == 0)
    { // VERTICAL -> NONE
        event->newPlayerYPos -= player->getPowerLVL() > 0 ? 32 : 0;
        event->vOLDDir.push_back(Mario::Animations::Bot);
        event->vOLDLength.push_back(player->getHitBoxY());

        event->vOLDDir.push_back(Mario::Animations::Nothing);
        event->vOLDLength.push_back(35);

        for (int i = 0; i < 3; i++)
        {
            event->redraw.add({leftBlockPos.x, leftBlockPos.y - i});
            event->redraw.add({rightBlockPos.x, rightBlockPos.y - i});
        }
    }
    else if (iType == 1)
    {
        event->newPlayerXPos += 32 - player->getHitBoxX() / 2;

        event->vOLDDir.push_back(Mario::Animations::Right);
        event->vOLDLength.push_back(player->getHitBoxX());

        event->vOLDDir.push_back(Mario::Animations::Nothing);
        event->vOLDLength.push_back(35);

        event->vNEWDir.push_back(Mario::Animations::PlayPipeTop);
        event->vNEWLength.push_back(1);

        event->vNEWDir.push_back(Mario::Animations::Nothing);
        event->vNEWLength.push_back(35);

        event->vNEWDir.push_back(Mario::Animations::Top);
        event->vNEWLength.push_back(player->getHitBoxY());

        for (int i = 0; i < 3; i++)
        {
            event->redraw.add({leftBlockPos.x, leftBlockPos.y + i});
            event->redraw.add({rightBlockPos.x, rightBlockPos.y + i});

            auto xID = event->newPlayerXPos - event->newMapXPos;
            auto x = map->getBlockIDX(xID);
            auto nextX = map->getBlockIDX(xID + 1);
            auto y = map->getBlockIDY(newPlayerPos.y) - 1 - i;

            event->redraw.add({x, y});
            event->redraw.add({nextX, y});
        }
    }
    else
    { // -- VERT -> VERT
        event->newPlayerXPos -=
            player->getPowerLVL() > 0 ? 32 : 0 - player->getHitBoxX() / 2;
        event->vOLDDir.push_back(Mario::Animations::Bot);
        event->vOLDLength.push_back(player->getHitBoxY());

        event->vOLDDir.push_back(Mario::Animations::Nothing);
        event->vOLDLength.push_back(55);

        for (int i = 0; i < 3; i++)
        {
            event->redraw.add({leftBlockPos.x, leftBlockPos.y - i});
            event->redraw.add({rightBlockPos.x, rightBlockPos.y - i});

            auto xID = event->newPlayerXPos - event->newMapXPos;
            auto x = map->getBlockIDX(xID);
            auto nextX = map->getBlockIDX(xID + 1);
            auto y = map->getBlockIDY(newPlayerPos.y) - 1 - i;

            event->redraw.add({x, y});
            event->redraw.add({nextX, y});
        }

        event->vNEWDir.push_back(Mario::Animations::PlayPipeTop);
        event->vNEWLength.push_back(1);

        event->vNEWDir.push_back(Mario::Animations::Nothing);
        event->vNEWLength.push_back(35);

        event->vNEWDir.push_back(Mario::Animations::Top);
        event->vNEWLength.push_back(player->getHitBoxY());
    }

    map->setInEvent(true);
}