#pragma once

#include "CommonHeader.h"

class Coin
{
public:
    Coin(int x, int y);

    void Update();
    void Draw(SDL_Renderer* rR);

    int getXPos();
    int getYPos();
    bool getDelete();

private:
    EA::Point<int> pos;
    int iLEFT = 80;

    int iSpriteID = 0;
    int iStepID = 0;

    bool bTOP = true;

    bool shouldDelete = false;
};