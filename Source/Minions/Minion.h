#pragma once

#include "Common/CFG.h"
#include "Graphics/IMG.h"

class Minion
{
public:
    virtual ~Minion() = default;

    virtual void Update() {};
    virtual void Draw(SDL_Renderer* rR, CIMG* iIMG) {}

    virtual void updateYPos(int iN);
    virtual void updateXPos();

    virtual bool updateMinion();
    virtual void minionPhysics();

    virtual void collisionEffect();

    virtual void minionDeathAnimation();

    void physicsState1();
    void physicsState2();

    void Spawn();
    void startJump(int iH);
    void resetJump();

    // ----- COLLISON

    virtual void collisionWithPlayer(bool TOP);
    virtual void points(int iPoints);

    virtual void collisionWithAnotherUnit() {}

    virtual void lockMinion() {};

    // ----- get & set -----
    int getBloockID() const;
    void setBlockID(int iBlockID);
    int getMinionState() const;

    virtual void setMinionState(int minionState);
    virtual bool getPowerUP();

    int getXPos();
    int getYPos();
    void setYPos(int iYPos);

    int minionState = 0;

    bool killOtherUnits = false;

    int iBlockID = 0;
    float fXPos, fYPos;
    int iHitBoxX = 32;
    int iHitBoxY = 32;
    bool minionSpawned = false;
    bool collisionOnlyWithPlayer = false;

    int deadTime = -1;

    bool onAnotherMinion = false;

    // ----- true = LEFT, false = RIGHT
    bool moveDirection = true;
    int moveSpeed = 1;

    int jumpState = 0;

    float startJumpSpeed = 6.65f;
    float currentJumpSpeed = 0;
    float jumpDistance = 0;
    float currentJumpDistance = 0;
    float currentFallingSpeed = 2.2f;
};