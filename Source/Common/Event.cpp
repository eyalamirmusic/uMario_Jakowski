#include "Event.h"
#include "Common/Core.h"

namespace Mario
{
void Event::draw(SDL_Renderer* rR)
{
    auto* map = CCore::getMap();

    for (auto& point: redraw)
    {
        if (point.x < map->getMapWidth())
        {
            auto id = map->getMapBlock(point)->getBlockID();
            auto* block = map->getBlock(id);
            auto mapX = (int) map->getXPos();

            auto x = 32 * point.x + mapX;
            auto y = CCFG::GAME_HEIGHT - 32 * point.y - 16;

            block->Draw(rR, x, y);
        }
    }
}

void Event::animation()
{
    switch (eventTypeID)
    {
        case eNormal:
        {
            normal();
            break;
        }
        case eEnd:
        {
            normal();
            end();
            break;
        }
        case eBossEnd:
        {
            normal();
            break;
        }
        default:
            normal();
            break;
    }
}

void Event::normal()
{
    auto map = CCore::getMap();
    auto player = map->getPlayer();

    auto speed = (float) iSpeed;

    if (state)
    {
        if (vOLDDir.size() > stepID)
        {
            if (vOLDLength[(int) stepID] > 0)
            {
                auto& length = vOLDLength[(int) stepID];

                switch (vOLDDir[(int) stepID])
                {
                    case Animations::eTOP: // TOP
                        player->setYPos((float) player->getYPos() - speed);
                        length -= speed;
                        break;
                    case Animations::eBOT:
                        player->setYPos((float) player->getYPos() + speed);
                        length -= speed;
                        break;
                    case Animations::eRIGHT:
                        player->setXPos((float) player->getXPos() + speed);
                        length -= speed;
                        player->moveAnimation();
                        player->setMoveDirection(true);
                        break;
                    case Animations::eRIGHTEND:
                        map->setXPos((float) map->getXPos() - speed);
                        length -= speed;
                        player->moveAnimation();
                        player->setMoveDirection(true);
                        break;
                    case Animations::eLEFT:
                        player->setXPos((float) player->getXPos() - speed);
                        length -= speed;
                        player->moveAnimation();
                        player->setMoveDirection(false);
                        break;
                    case Animations::eBOTRIGHTEND: // BOT & RIGHT
                        player->setYPos((float) player->getYPos() + speed);
                        map->setXPos((float) map->getXPos() - speed);
                        length -= speed;
                        player->moveAnimation();
                        break;
                    case Animations::eENDBOT1:
                        player->setYPos((float) player->getYPos() + speed);
                        length -= speed;
                        player->setMarioSpriteID(10);
                        break;
                    case Animations::eENDBOT2:
                        length -= speed;
                        player->setMoveDirection(false);
                        break;
                    case Animations::eENDPOINTS:
                        if (map->getMapTime() > 0)
                        {
                            map->setMapTime(map->getMapTime() - 1);
                            player->setScore(player->getScore() + 50);
                            if (!CCFG::getMusic()->isMusicPlaying())
                            {
                                CCFG::getMusic()->playTrack(
                                    Mario::Music::Tracks::Scorering);
                            }
                        }
                        else
                        {
                            length = 0;
                            CCFG::getMusic()->stopTrack();
                        }
                        map->getFlag()->UpdateCastleFlag();
                        break;
                    case Animations::eDEATHNOTHING:
                        length -= speed;
                        player->setMarioSpriteID(0);
                        break;
                    case Animations::eDEATHTOP: // DEATH TOP
                        player->setYPos((float) player->getYPos() - speed);
                        length -= speed;
                        player->setMarioSpriteID(0);
                        break;
                    case Animations::eDEATHBOT: // DEATH BOT
                        player->setYPos((float) player->getYPos() + speed);
                        length -= speed;
                        player->setMarioSpriteID(0);
                        break;
                    case Animations::eNOTHING: // NOTHING YAY
                        length -= 1;
                        break;
                    case Animations::ePLAYPIPERIGHT:
                        player->setXPos((float) player->getXPos() + speed);
                        length -= 1;
                        CCFG::getMusic()->playEffect(Mario::Music::Effects::Pipe);
                        break;
                    case Animations::eLOADINGMENU:
                        length -= 1;

                        if (length < 2)
                        {
                            map->setInEvent(false);
                            inEvent = false;
                            player->stopMove();

                            CCFG::getMM()->getLoadingMenu()->loadingType = true;
                            CCFG::getMM()->getLoadingMenu()->updateTime();
                            CCFG::getMM()->setViewID(CCFG::getMM()->eGameLoading);
                        }
                        break;
                    case Animations::eGAMEOVER:
                        length -= 1;

                        if (length < 2)
                        {
                            map->setInEvent(false);
                            inEvent = false;
                            player->stopMove();

                            CCFG::getMM()->getLoadingMenu()->loadingType = false;
                            CCFG::getMM()->getLoadingMenu()->updateTime();
                            CCFG::getMM()->setViewID(CCFG::getMM()->eGameLoading);

                            CCFG::getMusic()->playEffect(
                                Mario::Music::Effects::GameOver);
                        }
                        break;
                    case Animations::eBOSSEND1:
                        for (int i = map->getMapWidth() - 1; i > 0; i--)
                        {
                            if (map->getMapBlock(i, 6)->getBlockID() == 82)
                            {
                                map->getMapBlock(i, 6)->setBlockID(0);
                                break;
                            }
                        }
                        //CCore::getMap()->getMapBlock(CCore::getMap()->getBlockIDX((int)(CCore::getMap()->getPlayer()->getXPos() + CCore::getMap()->getPlayer()->getHitBoxX()/2 - CCore::getMap()->getXPos()) + vOLDLength[stepID] - 1), 6)->setBlockID(0);
                        map->clearPlatforms();
                        CCFG::getMusic()->playEffect(
                            Mario::Music::Effects::BridgeBreak);
                        length = 0;
                        player->setMoveDirection(false);
                        break;
                    case Animations::eBOSSEND2:
                        //CCore::getMap()->getMapBlock(CCore::getMap()->getBlockIDX((int)(CCore::getMap()->getPlayer()->getXPos() + CCore::getMap()->getPlayer()->getHitBoxX()/2 - CCore::getMap()->getXPos())) - 1, 5)->setBlockID(0);
                        //CCore::getMap()->getMapBlock(CCore::getMap()->getBlockIDX((int)(CCore::getMap()->getPlayer()->getXPos() + CCore::getMap()->getPlayer()->getHitBoxX()/2 - CCore::getMap()->getXPos())) - 1, 4)->setBlockID(0);
                        for (int i = map->getMapWidth() - 1; i > 0; i--)
                        {
                            if (map->getMapBlock(i, 5)->getBlockID() == 79)
                            {
                                map->getMapBlock(i, 5)->setBlockID(0);
                                break;
                            }
                        }
                        for (int i = map->getMapWidth() - 1; i > 0; i--)
                        {
                            if (map->getMapBlock(i, 4)->getBlockID() == 76)
                            {
                                map->getMapBlock(i, 4)->setBlockID(0);
                                break;
                            }
                        }
                        CCFG::getMusic()->playEffect(
                            Mario::Music::Effects::BridgeBreak);
                        length = 0;
                        break;
                    case Animations::eBOSSEND3:
                        for (int i = map->getMapWidth() - 1; i > 0; i--)
                        {
                            if (map->getMapBlock(i, 4)->getBlockID() == 76)
                            {
                                map->getMapBlock(i, 4)->setBlockID(0);
                                break;
                            }
                        }
                        //CCore::getMap()->getMapBlock(CCore::getMap()->getBlockIDX((int)(CCore::getMap()->getPlayer()->getXPos() + CCore::getMap()->getPlayer()->getHitBoxX()/2 - CCore::getMap()->getXPos())) - vOLDLength[stepID], 4)->setBlockID(0);
                        CCFG::getMusic()->playEffect(
                            Mario::Music::Effects::BridgeBreak);
                        player->setMoveDirection(true);
                        length = 0;
                        break;
                    case Animations::eBOSSEND4:
                        CCFG::getMusic()->playEffect(
                            Mario::Music::Effects::BowserFall);
                        length = 0;
                        break;
                    case Animations::eBOTRIGHTBOSS: // BOT & RIGHT
                        player->moveAnimation();
                        player->playerPhysics();
                        map->setXPos((float) map->getXPos() - speed);
                        length -= speed;
                        break;
                    case Animations::eBOSSTEXT1:
                        map->addText(length,
                                     CCFG::GAME_HEIGHT - 16 - 9 * 32,
                                     "THANK YOU MARIOz");
                        length = 0;
                        break;
                    case Animations::eBOSSTEXT2:
                        map->addText(length + 16,
                                     CCFG::GAME_HEIGHT - 16 - 7 * 32,
                                     "BUT OUR PRINCESS IS IN");
                        map->addText(length + 16,
                                     CCFG::GAME_HEIGHT - 16 - 6 * 32,
                                     "ANOTHER CASTLEz");
                        length = 0;
                        break;
                    case Animations::eENDGAMEBOSSTEXT1:
                        map->addText(length,
                                     CCFG::GAME_HEIGHT - 16 - 9 * 32,
                                     "THANK YOU MARIOz");
                        length = 0;
                        break;
                    case Animations::eENDGAMEBOSSTEXT2:
                        map->addText(length + 16,
                                     CCFG::GAME_HEIGHT - 16 - 7 * 32,
                                     "YOUR QUEST IS OVER.");
                        length = 0;
                        break;
                    case Animations::eMARIOSPRITE1:
                        player->setMarioSpriteID(1);
                        length = 0;
                        break;
                    case Animations::eVINE1:
                        player->setYPos((float) player->getYPos() - speed);
                        length -= speed;
                        player->setMarioSpriteID(10);
                        break;
                    case Animations::eVINE2:
                        player->setYPos((float) player->getYPos() - speed);
                        length -= speed;
                        player->setMarioSpriteID(11);
                        break;
                    case Animations::eVINESPAWN:
                        map->addVine(length,
                                     0,
                                     1,
                                     newLevelType == 0 || newLevelType == 4 ? 34
                                                                            : 36);
                        length = 0;
                        break;
                    case Animations::ePLAYPIPETOP:
                        break;
                }
            }
            else
            {
                ++stepID;
                iTime = SDL_GetTicks();
            }
        }
        else
        {
            if (!endGame)
            {
                if (SDL_GetTicks() >= iTime + iDelay)
                {
                    state = false;
                    stepID = 0;
                    newLevel();
                    player->stopMove();
                    if (inEvent)
                    {
                        CCFG::getMM()->getLoadingMenu()->updateTime();
                        CCFG::getMM()->getLoadingMenu()->loadingType = true;
                        CCFG::getMM()->setViewID(CCFG::getMM()->eGameLoading);
                        map->startLevelAnimation();
                    }

                    CCFG::keySpace = false;
                }
            }
            else
            {
                map->resetGameData();
                CCFG::getMM()->setViewID(CCFG::getMM()->eMainMenu);
                map->setInEvent(false);
                player->stopMove();
                inEvent = false;
                CCFG::keySpace = false;
                endGame = false;
                stepID = 0;
            }
        }
    }
    else
    {
        if (vNEWDir.size() > stepID)
        {
            if (vNEWLength[(int) stepID] > 0)
            {
                auto& originalLength = vNEWLength[(int) stepID];
                auto length = (float) originalLength;

                switch (vNEWDir[(int) stepID])
                {
                    case Animations::eTOP: // TOP
                        player->setYPos((float) player->getYPos() - speed);
                        length -= speed;
                        break;

                    case Animations::eBOT:
                        player->setYPos((float) player->getYPos() + speed);
                        length -= speed;
                        break;

                    case Animations::eRIGHT:
                        player->setXPos((float) player->getXPos() + speed);
                        length -= speed;
                        player->moveAnimation();
                        break;

                    case Animations::eLEFT:
                        player->setXPos((float) player->getXPos() - speed);
                        length -= speed;
                        player->moveAnimation();
                        break;

                    case Animations::ePLAYPIPETOP:
                        length -= 1;
                        CCFG::getMusic()->playEffect(Mario::Music::Effects::Pipe);
                        break;

                    case Animations::eNOTHING: // NOTHING YAY
                        length -= 1;
                        break;

                    case Animations::eVINE1:
                        player->setYPos((float) player->getYPos() - speed);
                        length -= speed;
                        player->setMarioSpriteID(10);
                        break;

                    case Animations::eVINE2:
                        player->setYPos((float) player->getYPos() - speed);
                        length -= speed;
                        player->setMarioSpriteID(11);
                        break;

                    case Animations::eRIGHTEND:
                    case Animations::eBOTRIGHTEND:
                    case Animations::eENDBOT1:
                    case Animations::eENDBOT2:
                    case Animations::eENDPOINTS:
                    case Animations::eDEATHNOTHING:
                    case Animations::eDEATHTOP:
                    case Animations::eDEATHBOT:
                    case Animations::ePLAYPIPERIGHT:
                    case Animations::eLOADINGMENU:
                    case Animations::eGAMEOVER:
                    case Animations::eBOSSEND1:
                    case Animations::eBOSSEND2:
                    case Animations::eBOSSEND3:
                    case Animations::eBOSSEND4:
                    case Animations::eBOTRIGHTBOSS:
                    case Animations::eBOSSTEXT1:
                    case Animations::eBOSSTEXT2:
                    case Animations::eENDGAMEBOSSTEXT1:
                    case Animations::eENDGAMEBOSSTEXT2:
                    case Animations::eMARIOSPRITE1:
                    case Animations::eVINESPAWN:
                        break;
                }

                originalLength = (int) length;
            }
            else
            {
                ++stepID;
            }
        }
        else
        {
            map->setInEvent(false);
            player->stopMove();
            CCFG::getMusic()->changeMusic(true, true);
            inEvent = false;
            CCFG::keySpace = false;
            CCore::resetKeys();
        }
    }
}

void Event::end()
{
    auto* flag = CCore::getMap()->getFlag();

    if (flag != nullptr && flag->iYPos < CCFG::GAME_HEIGHT - 16 - 3 * 32 - 4)
    {
        flag->Update();
    }
}

void Event::newLevel() const
{
    auto map = CCore::getMap();
    auto* player = map->getPlayer();

    map->setXPos((float) newMapXPos);

    player->setXPos((float) newPlayerXPos);
    player->setYPos((float) newPlayerYPos);
    map->setMoveMap(newMoveMap);
    
    if (map->getCurrentLevelID() != newCurrentLevel)
    {
        auto* mm = CCFG::getMM();

        mm->getLoadingMenu()->updateTime();
        mm->getLoadingMenu()->loadingType = true;
        mm->setViewID(mm->eGameLoading);

        player->setCoins(0);
    }

    map->setCurrentLevelID(newCurrentLevel);
    map->setLevelType(newLevelType);

    if (newUnderWater)
        player->resetRun();

    map->setUnderWater(newUnderWater);

    map->lockMinions();
}


void Event::resetData()
{
    vNEWDir.clear();
    vNEWLength.clear();
    vOLDDir.clear();
    vOLDLength.clear();
    resetRedraw();

    this->eventTypeID = eNormal;

    state = true;
    stepID = 0;
    inEvent = false;
    endGame = false;
    newUnderWater = false;
}

void Event::resetRedraw()
{
    redraw.clear();
}
} // namespace Mario