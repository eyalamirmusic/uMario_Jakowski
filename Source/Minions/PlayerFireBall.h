#pragma once

#include "Minion.h"

class PlayerFireBall : public Minion
{
public:
    PlayerFireBall(int X, int Y, bool moveDirection);

    void Update() override;
    void Draw(SDL_Renderer* rR, CIMG* iIMG) override;

    void updateXPos() override;

    void minionPhysics() override;

    void collisionWithPlayer(bool) override {}

    void collisionWithAnotherUnit() override;

    void collisionEffect() override {}
    void setMinionState(int) override {}

private:
    bool bDestroy;
    int destroyFrameID;
};
