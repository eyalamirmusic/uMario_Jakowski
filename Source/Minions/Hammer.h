#pragma once

#include "Minion.h"

class Hammer : public Minion
{
public:
    Hammer(int iXPos, int iYPos, bool moveDirection);

private:
    void Update() override;
    void Draw(SDL_Renderer* rR, CIMG* iIMG) override;

    void minionPhysics() override;
    void collisionWithPlayer(bool TOP) override;
};