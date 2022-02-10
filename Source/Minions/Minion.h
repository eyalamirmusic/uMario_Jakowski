#pragma once

#include "Common/CFG.h"
#include "Graphics/IMG.h"

enum class MinionJump
{
    None,
    Jump,
    Land,
    Fly
};

class Minion
{
public:
    virtual ~Minion() = default;

    virtual void update() {};
    virtual void draw(SDL_Renderer* rR, CIMG* iIMG) {}

    virtual void updateYPos(int iN);
    virtual void updateXPos();

    virtual bool updateMinion();
    virtual void minionPhysics();

    virtual void collisionEffect();

    virtual void minionDeathAnimation();

    virtual void collisionWithPlayer(bool TOP);
    virtual void points(int iPoints);

    virtual void collisionWithAnotherUnit() {}

    virtual void lockMinion() {};
    virtual void setMinionState(int minionState);

    void jumpPhysics();
    void physicsLand();

    void spawn();
    void startJump(int iH);
    void resetJump();

    int getBloockID() const;
    void setBlockID(int iBlockID);
    int getMinionState() const;

    int getXPos();
    int getYPos();
    void setYPos(int iYPos);

    int minionState = 0;

    bool killOtherUnits = false;

    int iBlockID = 0;
    float fXPos = 0.f, fYPos = 0.f;
    int iHitBoxX = 32;
    int iHitBoxY = 32;
    bool minionSpawned = false;
    bool collisionOnlyWithPlayer = false;

    int deadTime = -1;

    bool onAnotherMinion = false;

    // ----- true = LEFT, false = RIGHT
    bool moveDirection = true;
    int moveSpeed = 1;

    MinionJump jumpState = MinionJump::None;

    float startJumpSpeed = 6.65f;
    float currentJumpSpeed = 0.f;
    float jumpDistance = 0.f;
    float currentJumpDistance = 0.f;
    float currentFallingSpeed = 2.2f;
};

using MinionsVector = EA::Vector<EA::Vector<Minion*>>;
