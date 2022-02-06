#pragma once

#include "Minion.h"

class PlayerFireBall : public Minion
{
public:
    PlayerFireBall(int X, int Y, bool moveDirection);

private:
    void update() override;
    void draw(SDL_Renderer* rR, CIMG* iIMG) override;

    void updateXPos() override;

    void minionPhysics() override;

    void collisionWithPlayer(bool) override {}

    void collisionWithAnotherUnit() override;

    void collisionEffect() override {}
    void setMinionState(int) override {}

    bool bDestroy;
    int destroyFrameID;
};
