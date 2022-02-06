#pragma once

#include "Minion.h"

class Mushroom : public Minion
{
public:
    Mushroom(int iXPos, int iYPos, bool powerUP, int iX, int iY);

private:
    void update() override;
    bool updateMinion() override;

    void draw(SDL_Renderer* rR, CIMG* iIMG) override;

    void collisionWithPlayer(bool TOP) override;
    void setMinionState(int) override {};

    bool inSpawnState;
    int inSpawnY;
    bool powerUP;
    int iX, iY; // inSpawnState draw Block
};