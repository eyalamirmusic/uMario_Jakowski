#pragma once

#include "Minion.h"

class BulletBillSpawner : public Minion
{
public:
    BulletBillSpawner(int iXPos, int iYPos, int minionState);

private:
    void update() override;

    int nextBulletBillFrameID = 12;
};