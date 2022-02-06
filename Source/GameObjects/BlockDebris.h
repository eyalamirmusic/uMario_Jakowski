#pragma once

#include "CommonHeader.h"
#include "Common/Vector2.h"

class BlockDebris
{
public:
    BlockDebris(int xToUse, int yToUse);

    void update();
    void draw(SDL_Renderer* rR);

    int getDebrisState();

private:
    // ----- 0 = Animation, -1 = Delete
    int debrisState = 0;

    Vector2 vPositionL;
    Vector2 vPositionR;
    Vector2 vPositionL2;
    Vector2 vPositionR2;

    int iFrameID = 0;

    float fSpeedX = 2.15f, fSpeedY = 1.f;

    bool bRotate = false;

};