#pragma once

#include "Minion.h"

class BulletBill : public Minion
{
public:
    BulletBill(int iXPos, int iYPos, bool moveDirection, int minionState);

private:
    void update() override;
    void draw(SDL_Renderer* rR, CIMG* iIMG) override;
    void collisionWithPlayer(bool TOP) override;
};