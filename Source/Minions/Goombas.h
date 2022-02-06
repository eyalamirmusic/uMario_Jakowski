#pragma once

#include "Minion.h"

class Goombas : public Minion
{
public:
    Goombas(int iX, int iY, int iBlockID, bool moveDirection);

private:

    void Update() override;
    void Draw(SDL_Renderer* rR, CIMG* iIMG) override;

    void collisionWithPlayer(bool TOP) override;

    void setMinionState(int minionState) override;
};