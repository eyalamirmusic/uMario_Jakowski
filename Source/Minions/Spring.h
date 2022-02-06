#pragma once

#include "Minion.h"

class Spring : public Minion
{
public:
    Spring(int iXPos, int iYPos);

private:
    void Update() override;
    void Draw(SDL_Renderer* rR, CIMG* iIMG) override;

    void minionPhysics() override {}
    void collisionWithPlayer(bool TOP) override;
    void setMinionState(int) override {};

    bool inAnimation;
    int nextFrameID;

    bool extraJump;
};
