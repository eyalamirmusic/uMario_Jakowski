#pragma once

#include "Minion.h"

class HammerBro : public Minion
{
public:
    HammerBro(int iXPos, int iYPos);

private:

    void update() override;
    void draw(SDL_Renderer* rR, CIMG* iIMG) override;

    void minionPhysics() override;
    void collisionWithPlayer(bool TOP) override;
    void collisionEffect() override;


    bool moveDIR;
    float moveDistance;

    int nextJumpFrameID;
    bool newY; // true = UP, false = DOWN

    int hammerID;
    int nextHammerFrameID;

};