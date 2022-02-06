#pragma once

#include "Minion.h"

class Koppa : public Minion
{
public:
    Koppa(int iX, int iY, int minionState, bool moveDirection, int iBlockID);

private:
    void update() override;
    void draw(SDL_Renderer* rR, CIMG* iIMG) override;

    void minionPhysics() override;
    void updateXPos() override;

    void collisionWithPlayer(bool TOP) override;
    void collisionEffect() override;

    void setMinionState(int minionState) override;

    void setMinion();
    // ----- MinionState, 0 & 3 = Alive with wings, 1 = Alive, 2 = Dead, 4 = Dead animation, -1 = Destroy

    int iDistance;
    bool flyDirection; // -- minionState 3
};