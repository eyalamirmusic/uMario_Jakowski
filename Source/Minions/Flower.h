#pragma once

#include "Minion.h"

class Flower : public Minion
{
public:
    Flower(int iXPos, int iYPos, int iX, int iY);

private:
    void Update() override;
    bool updateMinion() override;

    void Draw(SDL_Renderer* rR, CIMG* iIMG) override;

    void collisionWithPlayer(bool TOP) override;
    void setMinionState(int) override {}

    bool inSpawnState;
    int inSpawnY;
    int iX, iY; // inSpawnState draw Block
};