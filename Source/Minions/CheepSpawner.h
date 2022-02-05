#pragma once

#include "Minion.h"

class CheepSpawner : public Minion
{
public:
    CheepSpawner(int iXPos, int iXEnd);

private:

    void Update() override;
    void minionPhysics() override;

    void spawnCheep();
    void nextCheep();


    int iXEnd;

    unsigned int iSpawnTime;

};