#include "BulletBill.h"
#include "Common/Core.h"


BulletBill::BulletBill(int iXPos, int iYPos, bool moveDirection, int minionState)
{
    this->fXPos = (float) iXPos;
    this->fYPos = (float) iYPos - 2;

    this->moveDirection = CCore::getMap()->getPlayer()->getXPos()
                              - CCore::getMap()->getXPos()
                              + CCore::getMap()->getPlayer()->getHitBoxX() / 32
                          < fXPos + iHitBoxX / 32;
    this->moveSpeed = 4;

    this->iHitBoxY = 30;

    this->collisionOnlyWithPlayer = true;

    this->iBlockID = CCore::getMap()->getCurrentLevelID() == 22 ? 60 : 59;

    this->minionSpawned = true;

    this->minionState = minionState;

    this->currentJumpSpeed =
        (float) CCore::getMap()->getBlockIDX((int) (fXPos + 16));
    this->currentFallingSpeed = (float) CCore::getMap()->getBlockIDY((int) (fYPos));

    this->currentJumpDistance =
        (float) (CCore::getMap()->getCurrentLevelID() == 17 ? 73 * 32
                                                            : 0); // -- MIN X
    specialState = CCore::getMap()->getCurrentLevelID() == 17
                          ? 303 * 32
                          : CCore::getMap()->getMapWidth() * 32; // -- MAX X

    jumpState = MinionJump::None;

    getCFG().getMusic()->playEffect(Mario::Music::Effects::BulletBill);
}


void BulletBill::update()
{
    if (minionState != -2)
    {
        fXPos += moveDirection ? -moveSpeed : moveSpeed;

        if (fXPos + iHitBoxX < currentJumpDistance || fXPos > specialState)
        {
            minionState = -1;
        }
    }
    else
    {
        Minion::minionDeathAnimation();
    }
}

void BulletBill::draw(SDL_Renderer* rR, CIMG* iIMG)
{
    if (minionState != -2)
    {
        iIMG->draw(rR,
                   (int) fXPos + (int) CCore::getMap()->getXPos(),
                   (int) fYPos + 2,
                   moveDirection);
    }
    else
    {
        iIMG->drawVert(
            rR, (int) fXPos + (int) CCore::getMap()->getXPos(), (int) fYPos);
    }

    if (minionState == 0)
        CCore::getMap()->getBlock(145)->getSprite()->getTexture()->draw(
            rR,
            (int) (currentJumpSpeed * 32 + CCore::getMap()->getXPos()),
            (int) (getCFG().GAME_HEIGHT - 16 - currentFallingSpeed * 32) + 32);
}


void BulletBill::collisionWithPlayer(bool TOP)
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