#pragma once

#include "CommonHeader.h"

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

    EA::Point<int> leftBlockPos, rightBlockPos, newPlayerPos;

    // ----- MAP LVL ID
    int newCurrentLevel = 0;
    int newLevelType = 0;
    bool newMoveMap = false;
    bool newUnderWater = false;

    int iDelay = 0;

    int iSpeed = 0;
};