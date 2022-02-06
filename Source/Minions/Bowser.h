#pragma once

#include "Minion.h"

class Bowser : public Minion
{
public:
    Bowser(float fXPos, float fYPos, bool spawnHammer = false);

private:
    void update() override;
    void draw(SDL_Renderer* rR, CIMG* iIMG) override;

    void minionPhysics() override;

    void collisionWithPlayer(bool TOP) override;

    void createFire();
    // -- minionState, 0 = Normal, 1 = Shot, -1 = Dead

    int nextJumpFrameID;

    bool spawnHammer;
    int nextHammerFrameID, numOfHammers;

    int iMinBlockID, iMaxBlockID;
    bool moveDir;

    int nextFireFrameID;

    int iYFireStart;
    int iFireID;

};