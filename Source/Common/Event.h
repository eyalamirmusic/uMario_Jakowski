#pragma once

#include "CommonHeader.h"

namespace Mario
{
enum class Animations
{
    Top,
    Right,
    RightEnd,
    Bot,
    Left,
    BotRightEnd,
    EndBot1,
    EndBot2,
    EndPoints,
    DeathNothing,
    DeathTop,
    DeathBot,
    Nothing,
    PlayPipeRight,
    PlayPipeTop,
    LoadingMenu,
    GameOver,
    BossEnd1,
    BossEnd2,
    BossEnd3,
    BossEnd4,
    BotRightBoss,
    BossText1,
    BossText2,
    EndGameBossText1,
    EndGameBossText2,
    MarioSprite1,
    Vine1,
    Vine2,
    VineSpawn,
};

class Event
{
public:
    void resetData();

    void draw(SDL_Renderer* rR);
    void animation();
    void newLevel() const;
    void resetRedraw();

    Vector<Animations> vOLDDir;
    Vector<int> vOLDLength;

    Vector<Animations> vNEWDir;
    Vector<int> vNEWLength;

    Vector<Point<int>> redraw;

    enum eventType
    {
        eNormal,
        eEnd,
        eBossEnd,
    };

    eventType eventTypeID = eventType::eNormal;


    int iSpeed = 0;

    int newLevelType = false;
    int newMapXPos = false;
    int newPlayerXPos = false;
    int newPlayerYPos = false;
    bool newMoveMap = false;

    unsigned int iTime = 0;
    int iDelay = 0;

    int newCurrentLevel = 0;
    bool inEvent = false;
    bool newUnderWater = false;

    bool endGame = false;


private:
    void normal();
    void end();

    bool state = true; // true = OLD, false = NEW
    unsigned int stepID = 0;
};

} // namespace Mario
