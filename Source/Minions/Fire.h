#pragma once

#include "Minion.h"

class Fire : public Minion
{
private:
    // -- minionState, 0 = Alive, -1 = Dead

    int toYPos;

public:
    Fire(float fXPos, float fYPos, int toYPos);
    ~Fire(void);

    void Update();
    void Draw(SDL_Renderer* rR, CIMG* iIMG);

    void collisionWithPlayer(bool TOP);

    void minionPhysics();
};