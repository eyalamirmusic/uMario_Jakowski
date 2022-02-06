#pragma once

#include "Minion.h"

class FireBall : public Minion
{
public:
    FireBall(int iXPos, int iYPos, int radius, int nSliceID, bool moveDirection);

private:

    void draw(SDL_Renderer* rR, CIMG* iIMG) override;
    void update() override;
    void collisionWithPlayer(bool TOP) override;
    void minionPhysics() override {}
    void updateXPos() override {}

    int radius; // -- r
    double angle;

    int iCenterX, iCenterY;

    double slice;

    int sliceID;

};