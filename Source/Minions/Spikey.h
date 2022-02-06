#pragma once

#include "Minion.h"

class Spikey : public Minion
{
public:
    Spikey(int iXPos, int iYPos);

private:
    void update() override;
    void draw(SDL_Renderer* rR, CIMG* iIMG) override;

    void minionPhysics() override;

    void collisionWithPlayer(bool TOP) override;
};