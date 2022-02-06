#pragma once

#include "Minion.h"

class Spikey : public Minion
{

public:
    Spikey(int iXPos, int iYPos);

private:
    void Update() override;
    void Draw(SDL_Renderer* rR, CIMG* iIMG) override;

    void minionPhysics() override;

    void collisionWithPlayer(bool TOP) override;
};