#pragma once

#include "Minion.h"

class Spring : public Minion
{
private:
    bool inAnimation;
    int nextFrameID;

    bool extraJump;

public:
    Spring(int iXPos, int iYPos);
    ~Spring(void);

    void Update();
    void Draw(SDL_Renderer* rR, CIMG* iIMG);

    void minionPhysics();

    void collisionWithPlayer(bool TOP);

    void setMinionState(int minionState);
};
