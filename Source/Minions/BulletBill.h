#pragma once

#include "Minion.h"

class BulletBill : public Minion
{
public:
    BulletBill(int iXPos, int iYPos, bool moveDirection, int minionState);

private:
    void Update() override;
    void Draw(SDL_Renderer* rR, CIMG* iIMG) override;
    void collisionWithPlayer(bool TOP) override;
};