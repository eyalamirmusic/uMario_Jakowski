#pragma once

#include "CommonHeader.h"
#include "Graphics/IMG.h"

class Flag
{
public:
    Flag(int iXPos, int iYPos);

    void Update();
    void UpdateCastleFlag();
    void Draw(SDL_Renderer* rR, CIMG* iIMG);
    void DrawCastleFlag(SDL_Renderer* rR, CIMG* iIMG);

    int getBlockID() const { return iBlockID; }

    EA::Point<int> getPos() const { return pos; }

    EA::Point<int> pos;
    int iBlockID;

    int iYTextPos;
    int iPoints;

    int castleFlagExtraXPos;
    int castleFlagY;
};