#pragma once

#include "Minion.h"

class Toad : public Minion
{
public:
    Toad(int iXPos, int iYPos, bool peach);

private:
    void update() override {}
    void draw(SDL_Renderer* rR, CIMG* iIMG) override;

    void minionPhysics() override {}
    void collisionWithPlayer(bool) override {}

    void setMinionState(int) override {}
};