#pragma once

#include "Minion.h"

class Plant : public Minion
{
public:
    Plant(int fXPos, int fYPos, int iBlockID);

private:
    void update() override;
    void draw(SDL_Renderer* rR, CIMG* iIMG) override;

    void minionPhysics() override;

    void collisionWithPlayer(bool TOP) override;

    void collisionEffect() override {}
    void lockMinion() override;
    void setMinionState(int minionState) override;

    bool bWait;
    unsigned int iTime;

    bool lockPlant;

    int iLength;

    int X, Y;
};