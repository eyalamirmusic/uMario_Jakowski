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
            auto y = getCFG().GAME_HEIGHT - 32 * point.y - 16;

            block->Draw(rR, x, y);
        }
    }
}

void Event::animation()
{
    switch (eventTypeID)
    {
        case EventType::Normal:
        {
            normal();
            break;
        }
        case EventType::End:
        {
            normal();
            end();
            break;
        }
        case EventType::BossEnd:
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
                    case Animations::Top: // TOP
                        player->setYPos((float) player->getYPos() - speed);
                        length -= speed;
                        break;
                    case Animations::Bot:
                        player->setYPos((float) player->getYPos() + speed);
                        length -= speed;
                        break;
                    case Animations::Right:
                        player->setXPos((float) player->getXPos() + speed);
                        length -= speed;
                        player->moveAnimation();
                        player->setMoveDirection(true);
                        break;
                    case Animations::RightEnd:
                        map->setXPos((float) map->getXPos() - speed);
                        length -= speed;
                        player->moveAnimation();
                        player->setMoveDirection(true);
                        break;
                    case Animations::Left:
                        player->setXPos((float) player->getXPos() - speed);
                        length -= speed;
                        player->moveAnimation();
                        player->setMoveDirection(false);
                        break;
                    case Animations::BotRightEnd: // BOT & RIGHT
                        player->setYPos((float) player->getYPos() + speed);
                        map->setXPos((float) map->getXPos() - speed);
                        length -= speed;
                        player->moveAnimation();
                        break;
                    case Animations::EndBot1:
                        player->setYPos((float) player->getYPos() + speed);
                        length -= speed;
                        player->setMarioSpriteID(10);
                        break;
                    case Animations::EndBot2:
                        length -= speed;
                        player->setMoveDirection(false);
                        break;
                    case Animations::EndPoints:
                        if (map->getMapTime() > 0)
                        {
                            map->setMapTime(map->getMapTime() - 1);
                            player->setScore(player->getScore() + 50);
                            if (!getCFG().getMusic()->isMusicPlaying())
                            {
                                getCFG().getMusic()->playTrack(
                                    Mario::Music::Tracks::Scorering);
                            }
                        }
                        else
                        {
                            length = 0;
                            getCFG().getMusic()->stopTrack();
                        }
                        map->getFlag()->UpdateCastleFlag();
                        break;
                    case Animations::DeathNothing:
                        length -= speed;
                        player->setMarioSpriteID(0);
                        break;
                    case Animations::DeathTop: // DEATH TOP
                        player->setYPos((float) player->getYPos() - speed);
                        length -= speed;
                        player->setMarioSpriteID(0);
                        break;
                    case Animations::DeathBot: // DEATH BOT
                        player->setYPos((float) player->getYPos() + speed);
                        length -= speed;
                        player->setMarioSpriteID(0);
                        break;
                    case Animations::Nothing: // NOTHING YAY
                        length -= 1;
                        break;
                    case Animations::PlayPipeRight:
                        player->setXPos((float) player->getXPos() + speed);
                        length -= 1;
                        getCFG().getMusic()->playEffect(Mario::Music::Effects::Pipe);
                        break;
                    case Animations::LoadingMenu:
                        length -= 1;

                        if (length < 2)
                        {
                            map->setInEvent(false);
                            inEvent = false;
                            player->stopMove();

                            getCFG().getMM()->getLoadingMenu()->loadingType = true;
                            getCFG().getMM()->getLoadingMenu()->updateTime();
                            getCFG().getMM()->setViewID(GameStates::eGameLoading);
                        }
                        break;
                    case Animations::GameOver:
                        length -= 1;

                        if (length < 2)
                        {
                            map->setInEvent(false);
                            inEvent = false;
                            player->stopMove();

                            getCFG().getMM()->getLoadingMenu()->loadingType = false;
                            getCFG().getMM()->getLoadingMenu()->updateTime();
                            getCFG().getMM()->setViewID(GameStates::eGameLoading);

                            getCFG().getMusic()->playEffect(
                                Mario::Music::Effects::GameOver);
                        }
                        break;
                    case Animations::BossEnd1:
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
                        getCFG().getMusic()->playEffect(
                            Mario::Music::Effects::BridgeBreak);
                        length = 0;
                        player->setMoveDirection(false);
                        break;
                    case Animations::BossEnd2:
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
                        getCFG().getMusic()->playEffect(
                            Mario::Music::Effects::BridgeBreak);
                        length = 0;
                        break;
                    case Animations::BossEnd3:
                        for (int i = map->getMapWidth() - 1; i > 0; i--)
                        {
                            if (map->getMapBlock(i, 4)->getBlockID() == 76)
                            {
                                map->getMapBlock(i, 4)->setBlockID(0);
                                break;
                            }
                        }
                        //CCore::getMap()->getMapBlock(CCore::getMap()->getBlockIDX((int)(CCore::getMap()->getPlayer()->getXPos() + CCore::getMap()->getPlayer()->getHitBoxX()/2 - CCore::getMap()->getXPos())) - vOLDLength[stepID], 4)->setBlockID(0);
                        getCFG().getMusic()->playEffect(
                            Mario::Music::Effects::BridgeBreak);
                        player->setMoveDirection(true);
                        length = 0;
                        break;
                    case Animations::BossEnd4:
                        getCFG().getMusic()->playEffect(
                            Mario::Music::Effects::BowserFall);
                        length = 0;
                        break;
                    case Animations::BotRightBoss: // BOT & RIGHT
                        player->moveAnimation();
                        player->playerPhysics();
                        map->setXPos((float) map->getXPos() - speed);
                        length -= speed;
                        break;
                    case Animations::BossText1:
                        map->addText(length,
                                     getCFG().GAME_HEIGHT - 16 - 9 * 32,
                                     "THANK YOU MARIOz");
                        length = 0;
                        break;
                    case Animations::BossText2:
                        map->addText(length + 16,
                                     getCFG().GAME_HEIGHT - 16 - 7 * 32,
                                     "BUT OUR PRINCESS IS IN");
                        map->addText(length + 16,
                                     getCFG().GAME_HEIGHT - 16 - 6 * 32,
                                     "ANOTHER CASTLEz");
                        length = 0;
                        break;
                    case Animations::EndGameBossText1:
                        map->addText(length,
                                     getCFG().GAME_HEIGHT - 16 - 9 * 32,
                                     "THANK YOU MARIOz");
                        length = 0;
                        break;
                    case Animations::EndGameBossText2:
                        map->addText(length + 16,
                                     getCFG().GAME_HEIGHT - 16 - 7 * 32,
                                     "YOUR QUEST IS OVER.");
                        length = 0;
                        break;
                    case Animations::MarioSprite1:
                        player->setMarioSpriteID(1);
                        length = 0;
                        break;
                    case Animations::Vine1:
                        player->setYPos((float) player->getYPos() - speed);
                        length -= speed;
                        player->setMarioSpriteID(10);
                        break;
                    case Animations::Vine2:
                        player->setYPos((float) player->getYPos() - speed);
                        length -= speed;
                        player->setMarioSpriteID(11);
                        break;
                    case Animations::VineSpawn:
                        map->addVine(length,
                                     0,
                                     1,
                                     newLevelType == 0 || newLevelType == 4 ? 34
                                                                            : 36);
                        length = 0;
                        break;
                    case Animations::PlayPipeTop:
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
                        getCFG().getMM()->getLoadingMenu()->updateTime();
                        getCFG().getMM()->getLoadingMenu()->loadingType = true;
                        getCFG().getMM()->setViewID(GameStates::eGameLoading);
                        map->startLevelAnimation();
                    }

                    getCFG().keySpace = false;
                }
            }
            else
            {
                map->resetGameData();
                getCFG().getMM()->setViewID(GameStates::eMainMenu);
                map->setInEvent(false);
                player->stopMove();
                inEvent = false;
                getCFG().keySpace = false;
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
                    case Animations::Top: // TOP
                        player->setYPos((float) player->getYPos() - speed);
                        length -= speed;
                        break;

                    case Animations::Bot:
                        player->setYPos((float) player->getYPos() + speed);
                        length -= speed;
                        break;

                    case Animations::Right:
                        player->setXPos((float) player->getXPos() + speed);
                        length -= speed;
                        player->moveAnimation();
                        break;

                    case Animations::Left:
                        player->setXPos((float) player->getXPos() - speed);
                        length -= speed;
                        player->moveAnimation();
                        break;

                    case Animations::PlayPipeTop:
                        length -= 1;
                        getCFG().getMusic()->playEffect(Mario::Music::Effects::Pipe);
                        break;

                    case Animations::Nothing: // NOTHING YAY
                        length -= 1;
                        break;

                    case Animations::Vine1:
                        player->setYPos((float) player->getYPos() - speed);
                        length -= speed;
                        player->setMarioSpriteID(10);
                        break;

                    case Animations::Vine2:
                        player->setYPos((float) player->getYPos() - speed);
                        length -= speed;
                        player->setMarioSpriteID(11);
                        break;

                    case Animations::RightEnd:
                    case Animations::BotRightEnd:
                    case Animations::EndBot1:
                    case Animations::EndBot2:
                    case Animations::EndPoints:
                    case Animations::DeathNothing:
                    case Animations::DeathTop:
                    case Animations::DeathBot:
                    case Animations::PlayPipeRight:
                    case Animations::LoadingMenu:
                    case Animations::GameOver:
                    case Animations::BossEnd1:
                    case Animations::BossEnd2:
                    case Animations::BossEnd3:
                    case Animations::BossEnd4:
                    case Animations::BotRightBoss:
                    case Animations::BossText1:
                    case Animations::BossText2:
                    case Animations::EndGameBossText1:
                    case Animations::EndGameBossText2:
                    case Animations::MarioSprite1:
                    case Animations::VineSpawn:
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
            getCFG().getMusic()->changeMusic(true, true);
            inEvent = false;
            getCFG().keySpace = false;
            CCore::resetKeys();
        }
    }
}

void Event::end()
{
    auto* flag = CCore::getMap()->getFlag();

    if (flag != nullptr && flag->iYPos < getCFG().GAME_HEIGHT - 16 - 3 * 32 - 4)
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
        auto* mm = getCFG().getMM();

        mm->getLoadingMenu()->updateTime();
        mm->getLoadingMenu()->loadingType = true;
        mm->setViewID(GameStates::eGameLoading);

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

    eventTypeID = EventType::Normal;

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