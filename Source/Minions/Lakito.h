#pragma once

#include "Minion.h"

class Lakito : public Minion
{
public:
    Lakito(int iXPos, int iYPos, int iMaxXPos);

private:
    void Update() override;
    void Draw(SDL_Renderer* rR, CIMG* iIMG) override;
    void collisionWithPlayer(bool TOP) override;
    void minionPhysics() override {}

    int iMaxXPos;
    bool end;

    bool followPlayer;

    int nextSpikeyFrameID;

};