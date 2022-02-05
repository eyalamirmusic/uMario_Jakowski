#pragma once

#include "Minion.h"

class Lakito : public Minion
{
private:
    int iMaxXPos;
    bool end;

    bool followPlayer;

    int nextSpikeyFrameID;

public:
    Lakito(int iXPos, int iYPos, int iMaxXPos);
    ~Lakito(void);

    void Update();
    void Draw(SDL_Renderer* rR, CIMG* iIMG);

    void minionPhysics();

    void collisionWithPlayer(bool TOP);
};