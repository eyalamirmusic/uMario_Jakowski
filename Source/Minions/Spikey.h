#pragma once

#include "Minion.h"

class Spikey : public Minion
{
private:
public:
    Spikey(int iXPos, int iYPos);
    ~Spikey(void);

    void Update();
    void Draw(SDL_Renderer* rR, CIMG* iIMG);

    void minionPhysics();

    void collisionWithPlayer(bool TOP);
};