#include "BlockDebris.h"
#include "Common/CFG.h"
#include "Common/Core.h"

BlockDebris::BlockDebris(int xToUse, int yToUse)
{
    vPositionL = {xToUse, yToUse};
    vPositionR = {xToUse + 16, yToUse};
    vPositionL2 = {xToUse, yToUse + 16};
    vPositionR2 = {xToUse + 16, yToUse + 16};
}

void BlockDebris::update()
{
    ++iFrameID;

    if (iFrameID > 4)
    {
        bRotate = !bRotate;
        iFrameID = 0;
    }

    vPositionL.setX((int) (vPositionL.getX() - fSpeedX));
    vPositionL.setY((int) (vPositionL.getY() + (fSpeedY - 3.0f)
                            + (fSpeedY < 3      ? fSpeedY < 2.5f ? -3 : -1.5f
                               : fSpeedY < 3.5f ? 1.5f
                                                : 3)));

    vPositionR.setX((int) (vPositionR.getX() + fSpeedX));
    vPositionR.setY((int) (vPositionR.getY() + (fSpeedY - 3.0f)
                            + (fSpeedY < 3      ? fSpeedY < 2.5f ? -3 : -1.5f
                               : fSpeedY < 3.5f ? 1.5f
                                                : 3)));

    vPositionL2.setX((int) (vPositionL2.getX() - (fSpeedX - 1.1f)));
    vPositionL2.setY((int) (vPositionL2.getY() + (fSpeedY - 1.5f)
                             + (fSpeedY < 1.5    ? fSpeedY < 1.3f ? -3 : -1
                                : fSpeedY < 1.8f ? 1
                                                 : 3)));

    vPositionR2.setX((int) (vPositionR2.getX() + (fSpeedX - 1.1f)));
    vPositionR2.setY((int) (vPositionR2.getY() + (fSpeedY - 1.5f)
                             + (fSpeedY < 1.5    ? fSpeedY < 1.3f ? -3 : -1
                                : fSpeedY < 1.8f ? 1
                                                 : 3)));

    fSpeedY *= 1.09f;
    fSpeedX *= 1.005f;

    if (vPositionL.getY() >= getCFG().GAME_HEIGHT)
    {
        debrisState = -1;
    }
}

void BlockDebris::draw(SDL_Renderer* rR)
{
    CCore::getMap()
        ->getBlock(CCore::getMap()->getLevelType() == 0
                           || CCore::getMap()->getLevelType() == 4
                       ? 64
                   : CCore::getMap()->getLevelType() == 1 ? 65
                                                          : 66)
        ->getSprite()
        ->getTexture()
        ->draw(rR,
               vPositionL.getX() + (int) CCore::getMap()->getXPos(),
               vPositionL.getY(),
               bRotate);
    CCore::getMap()
        ->getBlock(CCore::getMap()->getLevelType() == 0
                           || CCore::getMap()->getLevelType() == 4
                       ? 64
                   : CCore::getMap()->getLevelType() == 1 ? 65
                                                          : 66)
        ->getSprite()
        ->getTexture()
        ->draw(rR,
               vPositionR.getX() + (int) CCore::getMap()->getXPos(),
               vPositionR.getY(),
               bRotate);
    CCore::getMap()
        ->getBlock(CCore::getMap()->getLevelType() == 0
                           || CCore::getMap()->getLevelType() == 4
                       ? 64
                   : CCore::getMap()->getLevelType() == 1 ? 65
                                                          : 66)
        ->getSprite()
        ->getTexture()
        ->draw(rR,
               vPositionL2.getX() + (int) CCore::getMap()->getXPos(),
               vPositionL2.getY(),
               bRotate);
    CCore::getMap()
        ->getBlock(CCore::getMap()->getLevelType() == 0
                           || CCore::getMap()->getLevelType() == 4
                       ? 64
                   : CCore::getMap()->getLevelType() == 1 ? 65
                                                          : 66)
        ->getSprite()
        ->getTexture()
        ->draw(rR,
               vPositionR2.getX() + (int) CCore::getMap()->getXPos(),
               vPositionR2.getY(),
               bRotate);
}

/* ******************************************** */

int BlockDebris::getDebrisState()
{
    return debrisState;
}