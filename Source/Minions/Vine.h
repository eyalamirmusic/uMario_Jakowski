#pragma once

#include "Minion.h"

class Vine : public Minion
{
public:
    Vine(int iXPos, int iYPos, int minionState, int iBlockID);

private:
    // -- minionState = 0 VINE START, minionState = 1 VINE END

    void Update() override;
    void Draw(SDL_Renderer* rR, CIMG* iIMG) override;

    void minionPhysics() override {};

    void collisionWithPlayer(bool TOP) override;

    int iX, iY;
};