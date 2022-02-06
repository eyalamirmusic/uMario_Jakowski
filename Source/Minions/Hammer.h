#pragma once

#include "Minion.h"

class Hammer : public Minion
{
public:
    Hammer(int iXPos, int iYPos, bool moveDirection);

private:
    void update() override;
    void draw(SDL_Renderer* rR, CIMG* iIMG) override;

    void minionPhysics() override;
    void collisionWithPlayer(bool TOP) override;
};