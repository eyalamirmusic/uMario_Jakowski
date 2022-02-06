#include "Minion.h"
#include "Common/Core.h"

bool Minion::updateMinion()
{
    if (!minionSpawned)
        spawn();
    else
        minionPhysics();

    return minionSpawned;
}

void Minion::minionPhysics()
{
    if (jumpState == 1)
        physicsState1();
    else
    {
        auto map = CCore::getMap();

        if (!map->checkCollisionLB((int) fXPos + 2, (int) fYPos + 2, iHitBoxY, true)
            && !map->checkCollisionRB(
                (int) fXPos - 2, (int) fYPos + 2, iHitBoxX, iHitBoxY, true)
            && !onAnotherMinion)
        {
            physicsState2();
        }
        else
        {
            jumpState = 0;
            onAnotherMinion = false;
        }
    }
}

void Minion::physicsState1()
{
    updateYPos(-(int) currentJumpSpeed);
    currentJumpDistance += (int) currentJumpSpeed;

    currentJumpSpeed *=
        (currentJumpDistance / jumpDistance > 0.75f ? 0.972f : 0.986f);

    if (currentJumpSpeed < 2.5f)
    {
        currentJumpSpeed = 2.5f;
    }

    if (jumpDistance <= currentJumpDistance)
    {
        jumpState = 2;
    }
}

void Minion::physicsState2()
{
    currentFallingSpeed *= 1.06f;

    if (currentFallingSpeed > startJumpSpeed)
    {
        currentFallingSpeed = startJumpSpeed;
    }

    updateYPos((int) currentFallingSpeed);

    jumpState = 2;

    if (fYPos >= getCFG().GAME_HEIGHT)
    {
        minionState = -1;
    }
}

void Minion::updateXPos()
{
    // ----- LEFT
    auto* map = CCore::getMap();

    if (moveDirection)
    {
        if (map->checkCollisionLB(
                (int) fXPos - moveSpeed, (int) fYPos - 2, iHitBoxY, true)
            || map->checkCollisionLT((int) fXPos - moveSpeed, (int) fYPos + 2, true))
        {
            moveDirection = !moveDirection;

            if (killOtherUnits && fXPos > -map->getXPos() - 64
                && fXPos < -map->getXPos() + getCFG().GAME_WIDTH + 64 + iHitBoxX)
            {
                getCFG().getMusic()->playEffect(Mario::Music::Effects::BlockHit);
            }
        }
        else
        {
            if (jumpState == 0)
                fXPos -= (float) moveSpeed;
            else
                fXPos -= (float) moveSpeed / 2.0f;
        }
    }
    // ----- RIGHT
    else
    {
        if (map->checkCollisionRB(
                (int) fXPos + moveSpeed, (int) fYPos - 2, iHitBoxX, iHitBoxY, true)
            || map->checkCollisionRT(
                (int) fXPos + moveSpeed, (int) fYPos + 2, iHitBoxX, true))
        {
            moveDirection = !moveDirection;
            
            if (killOtherUnits && fXPos > -map->getXPos() - 64
                && fXPos < -map->getXPos()
                               + float(getCFG().GAME_WIDTH + 64 + iHitBoxX))
            {
                getCFG().getMusic()->playEffect(Mario::Music::Effects::BlockHit);
            }
        }
        else
        {
            fXPos += (jumpState == 0 ? (float) moveSpeed : (float) moveSpeed / 2.0f);
        }
    }

    if (fXPos < (float) -iHitBoxX)
    {
        minionState = -1;
    }
}

void Minion::updateYPos(int iN)
{
    auto map = CCore::getMap();
    if (iN > 0)
    {
        if (!map->checkCollisionLB((int) fXPos + 2, (int) fYPos + iN, iHitBoxY, true)
            && !map->checkCollisionRB(
                (int) fXPos - 2, (int) fYPos + iN, iHitBoxX, iHitBoxY, true))
        {
            fYPos += iN;
        }
        else
        {
            if (jumpState == 1)
                jumpState = 2;

            updateYPos(iN - 1);
        }
    }
    else if (iN < 0)
    {
        if (!map->checkCollisionLT((int) fXPos + 2, (int) fYPos + iN, true)
            && !map->checkCollisionRT(
                (int) fXPos - 2, (int) fYPos + iN, iHitBoxX, true))
        {
            fYPos += iN;
        }
        else
        {
            if (jumpState == 1)
            {
                jumpState = 2;
            }
            updateYPos(iN + 1);
        }
    }

    if ((int) fYPos % 2 == 1)
    {
        fYPos += 1;
    }
}

void Minion::collisionEffect()
{
    if (minionSpawned)
        moveDirection = !moveDirection;
}

void Minion::collisionWithPlayer(bool TOP)
{
}

void Minion::spawn()
{
    Map* map = CCore::getMap();
    auto x = map->getXPos();

    if ((fXPos >= -x && fXPos <= -x + getCFG().GAME_WIDTH)
        || (fXPos + iHitBoxX >= -x && fXPos + iHitBoxX <= -x + getCFG().GAME_WIDTH))
    {
        minionSpawned = true;
    }
}

void Minion::startJump(int iH)
{
    jumpState = 1;
    currentJumpSpeed = startJumpSpeed;
    jumpDistance = 32 * iH + 16.0f;
    currentJumpDistance = 0;
}

void Minion::resetJump()
{
    jumpState = 0;
    currentFallingSpeed = 2.7f;
}

void Minion::points(int iPoints)
{
    auto map = CCore::getMap();
    auto player = map->getPlayer();
    int points = iPoints * player->getComboPoints();

    map->addPoints((int) fXPos + 7, (int) fYPos, std::to_string(points), 8, 16);
    player->setScore(player->getScore() + points);
    player->addComboPoints();
}

void Minion::minionDeathAnimation()
{
    fXPos += (moveDirection ? -1.5f : 1.5f);
    fYPos += 2 * (deadTime > 8 ? -1 : deadTime > 2 ? 1 : 4.25f);

    if (deadTime > 0)
    {
        --deadTime;
    }

    if (fYPos > getCFG().GAME_HEIGHT)
    {
        minionState = -1;
    }
}

int Minion::getBloockID() const
{
    return iBlockID;
}

void Minion::setBlockID(int iBlockID)
{
    this->iBlockID = iBlockID;
}

int Minion::getXPos()
{
    return (int) fXPos;
}

int Minion::getYPos()
{
    return (int) fYPos;
}

void Minion::setYPos(int iYPos)
{
    this->fYPos = (float) iYPos;
}

int Minion::getMinionState() const
{
    return minionState;
}

void Minion::setMinionState(int minionState)
{
    this->minionState = minionState;

    if (minionState == -2)
    {
        deadTime = 16;
        fYPos -= iHitBoxY / 4;
        points(200);
        collisionOnlyWithPlayer = true;
        getCFG().getMusic()->playEffect(Mario::Music::Effects::Shot);
    }
}

bool Minion::getPowerUP()
{
    return true;
}