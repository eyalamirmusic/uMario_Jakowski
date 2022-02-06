#pragma once

#include "Minion.h"

class Star : public Minion
{
public:
    Star(int iXPos, int iYPos, int iX, int iY);

private:
    void update() override;
    bool updateMinion() override;

    void minionPhysics() override;

    void draw(SDL_Renderer* rR, CIMG* iIMG) override;

    void collisionWithPlayer(bool TOP) override;
    void setMinionState(int) override {};

    bool inSpawnState;
    int inSpawnY;
    int iX, iY; // inSpawnState draw Block
};