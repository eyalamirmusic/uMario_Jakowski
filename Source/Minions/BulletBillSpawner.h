#pragma once

#include "Minion.h"

class BulletBillSpawner : public Minion
{
public:
    BulletBillSpawner(int iXPos, int iYPos, int minionState);

    void Update() override;

private:
    int nextBulletBillFrameID = 12;

};