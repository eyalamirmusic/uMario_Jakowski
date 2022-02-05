#pragma once

#include "CommonHeader.h"
#include "Graphics/IMG.h"

class Flag
{
private:
public:
    Flag(int iXPos, int iYPos);
    ~Flag(void);

    int iXPos, iYPos;
    int iBlockID;

    int iYTextPos;
    int iPoints;

    int castleFlagExtraXPos;
    int castleFlagY;

    void Update();
    void UpdateCastleFlag();
    void Draw(SDL_Renderer* rR, CIMG* iIMG);
    void DrawCastleFlag(SDL_Renderer* rR, CIMG* iIMG);
};