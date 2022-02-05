#pragma once

#include "Minion.h"

class CheepSpawner : public Minion
{
private:
    int iXEnd;

    unsigned int iSpawnTime;

public:
    CheepSpawner(int iXPos, int iXEnd);
    ~CheepSpawner(void);

    void Update();
    void minionPhysics();

    void spawnCheep();
    void nextCheep();
};