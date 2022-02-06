#pragma once

#include "Minion.h"

class Squid : public Minion
{
public:
    Squid(int iXPos, int iYPos);

private:
    void update() override;
    void draw(SDL_Renderer* rR, CIMG* iIMG) override;

    void minionPhysics() override {}
    void collisionWithPlayer(bool TOP) override;

    void changeBlockID();

    int moveXDistance, moveYDistance;
};