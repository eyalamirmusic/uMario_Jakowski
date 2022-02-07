#include "PlayerFireBall.h"
#include "Common/Core.h"

PlayerFireBall::PlayerFireBall(int iXPos, int iYPos, bool moveDirection)
{
    this->fXPos = (float) iXPos;
    this->fYPos = (float) iYPos;

    this->moveDirection = moveDirection;

    this->killOtherUnits = true;

    this->minionSpawned = true;

    this->moveSpeed = 14;

    this->iBlockID = 62;

    this->jumpState = MinionJump::Land;

    this->iHitBoxX = 16;
    this->iHitBoxY = 16;

    this->bDestroy = false;

    this->destroyFrameID = 15;
}

void PlayerFireBall::update()
{
    if (bDestroy)
    {
        if (destroyFrameID > 10)
        {
            this->iBlockID = 63;
        }
        else if (destroyFrameID > 5)
        {
            this->iBlockID = 64;
        }
        else if (destroyFrameID > 0)
        {
            this->iBlockID = 65;
        }
        else
        {
            minionState = -1;
        }
        --destroyFrameID;
    }
    else
    {
        if (jumpState == MinionJump::None)
        {
            jumpState = MinionJump::Jump;
            currentJumpSpeed = startJumpSpeed;
            jumpDistance = 34.0f;
            currentJumpDistance = 0;
        }
        else if (jumpState == MinionJump::Jump)
        {
            updateYPos(-1);
            currentJumpDistance += 1;

            if (jumpDistance <= currentJumpDistance)
            {
                jumpState = MinionJump::Land;
            }
        }
        else
        {
            if (!CCore::getMap()->checkCollisionLB(
                    (int) fXPos + 2, (int) fYPos + 2, iHitBoxY, true)
                && !CCore::getMap()->checkCollisionRB(
                    (int) fXPos - 2, (int) fYPos + 2, iHitBoxX, iHitBoxY, true)
                && !onAnotherMinion)
            {
                updateYPos(1);

                jumpState = MinionJump::Land;

                if (fYPos >= getCFG().GAME_HEIGHT)
                {
                    minionState = -1;
                }
            }
            else
            {
                jumpState = MinionJump::None;
                onAnotherMinion = false;
            }
        }

        updateXPos();
    }
}

void PlayerFireBall::draw(SDL_Renderer* rR, CIMG* iIMG)
{
    if (!bDestroy)
    {
        iIMG->draw(rR,
                   (int) fXPos + (int) CCore::getMap()->getXPos(),
                   (int) fYPos,
                   !moveDirection);
    }
    else
    {
        iIMG->draw(rR,
                   (int) fXPos + (int) CCore::getMap()->getXPos()
                       - (moveDirection ? 16 : 0),
                   (int) fYPos - 8,
                   !moveDirection);
    }
}

void PlayerFireBall::updateXPos()
{
    // ----- LEFT
    if (moveDirection)
    {
        if (CCore::getMap()->checkCollisionLB(
                (int) fXPos - moveSpeed, (int) fYPos - 2, iHitBoxY, true)
            || CCore::getMap()->checkCollisionLT(
                (int) fXPos - moveSpeed, (int) fYPos + 2, true))
        {
            bDestroy = true;
            collisionOnlyWithPlayer = true;
            getCFG().getMusic()->playEffect(Mario::Music::Effects::BlockHit);
        }
        else
        {
            fXPos -= (jumpState == MinionJump::None ? moveSpeed : moveSpeed / 2.0f);
        }
    }
    // ----- RIGHT
    else
    {
        if (CCore::getMap()->checkCollisionRB(
                (int) fXPos + moveSpeed, (int) fYPos - 2, iHitBoxX, iHitBoxY, true)
            || CCore::getMap()->checkCollisionRT(
                (int) fXPos + moveSpeed, (int) fYPos + 2, iHitBoxX, true))
        {
            bDestroy = true;
            collisionOnlyWithPlayer = true;
            getCFG().getMusic()->playEffect(Mario::Music::Effects::BlockHit);
        }
        else
        {
            fXPos += (jumpState == MinionJump::None ? moveSpeed : moveSpeed / 2.0f);
        }
    }

    if (fXPos < -iHitBoxX)
    {
        minionState = -1;
    }
}

void PlayerFireBall::minionPhysics()
{
    if (!bDestroy)
        Minion::minionPhysics();
}

void PlayerFireBall::collisionWithAnotherUnit()
{
    bDestroy = true;
    collisionOnlyWithPlayer = true;
}