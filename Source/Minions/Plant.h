#pragma once

#include "Minion.h"

class Plant : public Minion
{
public:
    Plant(int fXPos, int fYPos, int iBlockID);

    void Update() override;
    void Draw(SDL_Renderer* rR, CIMG* iIMG) override;

    void minionPhysics() override;

    void collisionWithPlayer(bool TOP) override;

    void collisionEffect() override {}
    void lockMinion() override;
    void setMinionState(int minionState) override;

private:
    bool bWait;
    unsigned int iTime;

    bool lockPlant;

    int iLength;

    int X, Y;
};