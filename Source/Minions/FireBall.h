#pragma once

#include "Minion.h"

class FireBall : public Minion
{
public:
    FireBall(int iXPos, int iYPos, int radius, int nSliceID, bool moveDirection);

private:

    void Draw(SDL_Renderer* rR, CIMG* iIMG) override;
    void Update() override;
    void collisionWithPlayer(bool TOP) override;
    void minionPhysics() override {}
    void updateXPos() override {}

    int radius; // -- r
    double angle;

    int iCenterX, iCenterY;

    double slice;

    int sliceID;

};