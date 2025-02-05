#include "HammerBro.h"
#include "Common/Core.h"
#include <cstdlib>
#include <ctime>

HammerBro::HammerBro(int iXPos, int iYPos)
{
    this->fXPos = (float) iXPos;
    this->fYPos = (float) iYPos + 18;

    this->moveDIR = true;
    this->moveDirection = true;
    this->moveSpeed = 1;
    this->minionState = 0;

    this->iHitBoxX = 32;
    this->iHitBoxY = 48;

    this->iBlockID =
        CCore::getMap()->getLevelType() == 0 || CCore::getMap()->getLevelType() == 4
            ? 43
            : 45;

    this->moveDistance = 16.0f;

    this->newY = true;

    srand((unsigned) time(nullptr));

    this->nextJumpFrameID = rand() % 175 + 125;
    this->currentJumpDistance = 0;
    this->jumpDistance = 0;

    this->hammerID = 0;
    this->nextHammerFrameID = 65;
}

void HammerBro::update()
{
    if (minionState != -2)
    {
        moveDirection =
            !(CCore::getMap()->getPlayer()->getXPos() - CCore::getMap()->getXPos()
                  + CCore::getMap()->getPlayer()->getHitBoxX() / 2
              > fXPos + iHitBoxX / 2);

        if (moveDistance > 0)
        {
            moveDistance -= 0.5f;

            if (jumpState == MinionJump::Jump)
            {
                fXPos += moveDIR ? -0.5f : 0.5f;
            }
            if (moveDIR)
            {
                if (!CCore::getMap()->checkCollisionLB(
                        (int) fXPos - moveSpeed, (int) fYPos - 2, iHitBoxY, true)
                    && !CCore::getMap()->checkCollisionLT(
                        (int) fXPos - moveSpeed, (int) fYPos + 2, true))
                {
                    fXPos += -0.5f;
                }
            }
            else
            {
                if (!CCore::getMap()->checkCollisionRB((int) fXPos + moveSpeed,
                                                       (int) fYPos - 2,
                                                       iHitBoxX,
                                                       iHitBoxY,
                                                       true)
                    && !CCore::getMap()->checkCollisionRT(
                        (int) fXPos + moveSpeed, (int) fYPos + 2, iHitBoxX, true))
                {
                    fXPos += 0.5f;
                }
            }
        }
        else
        {
            moveDistance = 1 * 32 + 16;
            moveDIR = !moveDIR;
        }

        if (currentJumpDistance > 0)
        {
            if (newY)
            {
                fYPos -= 4;
                currentJumpDistance -= 4;
            }
            else
            {
                if (jumpDistance > 0)
                {
                    fYPos -= 4;
                    jumpDistance -= 4;
                }
                else
                {
                    fYPos += 4;
                    currentJumpDistance -= 4;
                }
            }
        }
        else if (nextJumpFrameID < 0)
        {
            currentJumpDistance = 4 * 32 + 16;
            jumpDistance = 16;
            nextJumpFrameID = rand() % 295 + 215;
            jumpState = MinionJump::Jump;
            if (fYPos + iHitBoxY < getCFG().GAME_HEIGHT - 16 - 4 * 32)
            {
                newY = rand() % 3 == 0;
            }
            else
            {
                newY = true;
            }
        }
        else
        {
            --nextJumpFrameID;
            jumpState = MinionJump::Land;
        }

        if (nextHammerFrameID < 15)
        {
            this->iBlockID = CCore::getMap()->getLevelType() == 0
                                     || CCore::getMap()->getLevelType() == 4
                                 ? 44
                                 : 46;
        }
        else
        {
            this->iBlockID = CCore::getMap()->getLevelType() == 0
                                     || CCore::getMap()->getLevelType() == 4
                                 ? 43
                                 : 45;
        }

        if (nextHammerFrameID < 0)
        {
            nextHammerFrameID = rand() % 95 + 95;
            CCore::getMap()->addHammer(
                (int) (fXPos + iHitBoxX / 2), (int) (fYPos - 18), !moveDirection);
            if (hammerID < 2 - rand() % 2)
            {
                ++hammerID;
                nextHammerFrameID /= 4;
            }
            else
            {
                hammerID = 0;
            }
        }
        else
        {
            --nextHammerFrameID;
        }
    }
    else
    {
        Minion::minionDeathAnimation();
    }
}

void HammerBro::draw(SDL_Renderer* rR, CIMG* iIMG)
{
    if (minionState != -2)
    {
        iIMG->draw(rR,
                   (int) fXPos + (int) CCore::getMap()->getXPos(),
                   (int) fYPos - 18,
                   moveDirection);
    }
    else
    {
        iIMG->drawVert(
            rR, (int) fXPos + (int) CCore::getMap()->getXPos(), (int) fYPos - 18);
    }
}

void HammerBro::minionPhysics()
{
    if (jumpState == MinionJump::Jump) {}
    else
    {
        if (!CCore::getMap()->checkCollisionLB(
                (int) fXPos + 2, (int) fYPos + 2, iHitBoxY, true)
            && !CCore::getMap()->checkCollisionRB(
                (int) fXPos - 2, (int) fYPos + 2, iHitBoxX, iHitBoxY, true))
        {
            Minion::physicsLand();
        }
        else
        {
            jumpState = MinionJump::None;
        }
    }
}

void HammerBro::collisionWithPlayer(bool TOP)
{
    if (CCore::getMap()->getPlayer()->getStarEffect() || TOP)
    {
        setMinionState(-2);
    }
    else
    {
        CCore::getMap()->playerDeath(true, false);
    }
}

void HammerBro::collisionEffect()
{
}