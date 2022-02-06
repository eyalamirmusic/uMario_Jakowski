#pragma once

#include "Minion.h"

class UpFire : public Minion
{
public:
    UpFire(int iXPos, int iYJump);

private:
    void update() override;
    void draw(SDL_Renderer* rR, CIMG* iIMG) override;

    void minionPhysics() override;
    void collisionWithPlayer(bool TOP) override;

    // moveDirection true = TOP, false = BOT
    int iYJump;
    int nextJumpFrameID;
};