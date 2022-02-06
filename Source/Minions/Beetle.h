#pragma once

#include "Minion.h"

class Beetle : public Minion
{
public:
    Beetle(int iXPos, int iYPos, bool moveDirection);

private:
    void update() override;
    void draw(SDL_Renderer* rR, CIMG* iIMG) override;

    void collisionWithPlayer(bool TOP) override;
    void collisionEffect() override;
    void setMinionState(int minionState) override;
};