#pragma once

class Pipe
{
public:
    Pipe(int iType,
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
         bool underWater);

    void checkUse();
    void setEvent();

private:
    // ----- 0 = VERTICAL, 1 = HORIZONTAL -> VERTICAL, 2 = VERTICAL -> VERTICAL
    int iType = 0;

    // ----- X, Y LEFT Block Position
    int iLX = 0;
    int iLY = 0;
    // ----- X, Y RIGHT Block Position

    int iRX = 0;
    int iRY = 0;

    int newPlayerPosX = 0;
    int newPlayerPosY = 0;

    // ----- MAP LVL ID
    int newCurrentLevel = 0;
    int newLevelType = 0;
    bool newMoveMap = false;
    bool newUnderWater = false;

    int iDelay = 0;

    int iSpeed = 0;
};