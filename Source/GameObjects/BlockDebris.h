#pragma once

#include "CommonHeader.h"
#include "Common/Vector2.h"

class BlockDebris
{
private:
    // ----- 0 = Animation, -1 = Delete
    int debrisState;

    Vector2* vPositionL;
    Vector2* vPositionR;
    Vector2* vPositionL2;
    Vector2* vPositionR2;

    int iFrameID;

    float fSpeedX, fSpeedY;

    bool bRotate;

public:
    BlockDebris(int iXPos, int iYPos);
    ~BlockDebris(void);

    void Update();
    void Draw(SDL_Renderer* rR);

    int getDebrisState();
};