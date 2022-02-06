#pragma once

#include "Minion.h"

class UpFire : public Minion
{
public:
    UpFire(int iXPos, int iYJump);

    void Update() override;
    void Draw(SDL_Renderer* rR, CIMG* iIMG) override;

    void minionPhysics() override;
    void collisionWithPlayer(bool TOP) override;

private:
    // moveDirection true = TOP, false = BOT
    int iYJump;
    int nextJumpFrameID;
};