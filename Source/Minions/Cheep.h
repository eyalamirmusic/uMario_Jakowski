#pragma once

#include "Minion.h"

class Cheep : public Minion
{
public:
    Cheep(int iXPos,
          int iYPos,
          int minionType,
          int moveSpeed,
          bool moveDiretion = false);
private:
    void Update() override;
    void Draw(SDL_Renderer* rR, CIMG* iIMG) override;

    void minionPhysics() override;
    void collisionWithPlayer(bool TOP) override;


    bool moveY, moveYDIR;

};