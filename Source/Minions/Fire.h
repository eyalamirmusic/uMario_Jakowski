#pragma once

#include "Minion.h"

class Fire : public Minion
{
public:
    Fire(float fXPos, float fYPos, int toYPos);

private:
    void update() override;
    void draw(SDL_Renderer* rR, CIMG* iIMG) override;

    void collisionWithPlayer(bool TOP) override;

    void minionPhysics() override;

    // -- minionState, 0 = Alive, -1 = Dead
    int toYPos;

};