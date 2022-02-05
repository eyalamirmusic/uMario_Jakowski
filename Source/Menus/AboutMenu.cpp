#include "AboutMenu.h"
#include "Common/CFG.h"
#include "Common/Core.h"
#include <cstdlib>
#include <ctime>

AboutMenu::AboutMenu()
{
    lMO.createNew("MAIN MENU", 150, 340);
    srand((unsigned) time(nullptr));
}

void AboutMenu::update()
{
    if (SDL_GetTicks() >= iTime + 35)
    {
        this->cR = getColorStep(cR, nR);
        this->cG = getColorStep(cG, nG);
        this->cB = getColorStep(cB, nB);

        if (colorStepID >= 15 || (cR == nR && cG == nG && cB == nB))
        {
            nextColor();
            colorStepID = 1;
        }
        else
        {
            ++colorStepID;
        }

        CCore::getMap()->setLevelType(rand() % 4);

        if (rand() % 10 < 6)
        {
            CCore::getMap()->addGoombas(-(int) CCore::getMap()->getXPos()
                                            + rand() % (getCFG().GAME_WIDTH + 128),
                                        -32,
                                        rand() % 2 == 0);
            CCore::getMap()->addGoombas(-(int) CCore::getMap()->getXPos()
                                            + rand() % (getCFG().GAME_WIDTH + 128),
                                        -32,
                                        rand() % 2 == 0);
        }
        else if (rand() % 10 < 8)
        {
            CCore::getMap()->addKoppa(-(int) CCore::getMap()->getXPos()
                                          + rand() % (getCFG().GAME_WIDTH + 128),
                                      -32,
                                      0,
                                      rand() % 2 == 0);
            CCore::getMap()->addKoppa(-(int) CCore::getMap()->getXPos()
                                          + rand() % (getCFG().GAME_WIDTH + 128),
                                      -32,
                                      0,
                                      rand() % 2 == 0);
        }
        else if (rand() % 6 < 4)
        {
            CCore::getMap()->addFire(-CCore::getMap()->getXPos()
                                         + getCFG().GAME_WIDTH + 128,
                                     getCFG().GAME_HEIGHT - 16.0f - rand() % 16 * 32,
                                     getCFG().GAME_HEIGHT - 16 - rand() % 16 * 32);
        }
        else if (rand() % 6 < 4)
        {
            CCore::getMap()->addBulletBill(
                (int) (-CCore::getMap()->getXPos() + getCFG().GAME_WIDTH + 128),
                getCFG().GAME_HEIGHT - 16 - rand() % 16 * 32,
                true,
                1);
        }
        else
        {
            CCore::getMap()->addFireBall(
                -(int) CCore::getMap()->getXPos()
                    + rand() % (getCFG().GAME_WIDTH + 128) + 8,
                getCFG().GAME_HEIGHT - 16 - rand() % 16 * 32,
                rand() % 8 + 4 + 8,
                rand() % 360,
                rand() % 2 == 0);
        }

        //iNumOfUnits += 2;

        iTime = SDL_GetTicks();
    }

    if (moveDirection
        && getCFG().GAME_WIDTH - CCore::getMap()->getXPos()
               >= (CCore::getMap()->getMapWidth() - 20) * 32)
    {
        moveDirection = !moveDirection;
    }
    else if (!moveDirection && -CCore::getMap()->getXPos() <= 0)
    {
        moveDirection = !moveDirection;
    }

    CCore::getMap()->setXPos(CCore::getMap()->getXPos()
                             + 4 * (moveDirection ? -1 : 1));
    //CCore::getMap()->getPlayer()->setXPos((float)CCore::getMap()->getPlayer()->getXPos() + 4 * (moveDirection ? -1 : 1));
}

void AboutMenu::draw(SDL_Renderer* rR)
{
    getCFG().getText()->drawWS(rR, "MARIO V 1.03 - C++ AND SDL2", 150, 128, 0, 0, 0);
    getCFG().getText()->drawWS(rR, "AUTOR: LUKASZ JAKOWSKI", 150, 146, 0, 0, 0);

    getCFG().getText()->drawWS(rR, "INFORMATYKA INZ 2012-2016", 150, 188, 0, 0, 0);
    getCFG().getText()->drawWS(
        rR, "UNIWERSYTET SLASKI W KATOWICACH", 150, 206, 0, 0, 0);
    getCFG().getText()->drawWS(rR, "MAJ 2014", 150, 224, 0, 0, 0);

    getCFG().getText()->drawWS(rR, "WWW.LUKASZJAKOWSKI.PL", 150, 264, 0, 0, 0);

    //getCFG().getText()->DrawWS(rR, std::to_string(iNumOfUnits), 5, getCFG().GAME_HEIGHT - 21, 0, 0, 0);

    for (unsigned int i = 0; i < lMO.size(); i++)
    {
        getCFG().getText()->drawWS(
            rR, lMO[i]->getText(), lMO[i]->getXPos(), lMO[i]->getYPos(), 0, 0, 0);
    }

    getCFG().getMM()->getActiveOption()->draw(
        rR, lMO[activeMenuOption]->getXPos() - 32, lMO[activeMenuOption]->getYPos());
}

/* ******************************************** */

void AboutMenu::enter()
{
    getCFG().getMM()->resetActiveOptionID(Mario::MenuStates::MainMenu);
    getCFG().getMM()->setViewID(Mario::MenuStates::MainMenu);
    reset();
    getCFG().getMusic()->stopTrack();
}

/* ******************************************** */

void AboutMenu::launch()
{
    this->cR = 93;
    this->cG = 148;
    this->cB = 252;
}

void AboutMenu::reset()
{
    CCore::getMap()->setXPos(0);
    CCore::getMap()->loadLVL();
}

/* ******************************************** */

void AboutMenu::nextColor()
{
    int iN = iColorID;

    while (iN == iColorID)
    {
        iColorID = rand() % 16;
    }

    ++iColorID;

    switch (iColorID)
    {
        case 0:
            nR = 73;
            nG = 133;
            nB = 203;
            break;
        case 1:
            nR = 197;
            nG = 197;
            nB = 223;
            break;
        case 2:
            nR = 27;
            nG = 60;
            nB = 173;
            break;
        case 3:
            nR = 6;
            nG = 21;
            nB = 86;
            break;
        case 4:
            nR = 183;
            nG = 85;
            nB = 76;
            break;
        case 5:
            nR = 110;
            nG = 58;
            nB = 70;
            break;
        case 6:
            nR = 55;
            nG = 19;
            nB = 63;
            break;
        case 7:
            nR = 115;
            nG = 53;
            nB = 126;
            break;
        case 8:
            nR = 227;
            nG = 200;
            nB = 0;
            break;
        case 9:
            nR = 255;
            nG = 180;
            nB = 2;
            break;
        case 10:
            nR = 231;
            nG = 51;
            nB = 24;
            break;
        case 11:
            nR = 255;
            nG = 180;
            nB = 2;
            break;
        case 12:
            nR = 4;
            nG = 2;
            nB = 15;
            break;
        case 13:
            nR = 135;
            nG = 178;
            nB = 168;
            break;
        case 14:
            nR = 64;
            nG = 43;
            nB = 24;
            break;
        case 15:
            nR = rand() % 255;
            nG = rand() % 255;
            nB = rand() % 255;
            break;
    }
}

int AboutMenu::getColorStep(int iOld, int iNew)
{
    return iOld
           + (iOld > iNew ? (iNew - iOld) * colorStepID / 30
                          : (iNew - iOld) * colorStepID / 30);
}

/* ******************************************** */

void AboutMenu::setBackgroundColor(SDL_Renderer* rR)
{
    SDL_SetRenderDrawColor(rR, cR, cG, cB, 255);
}

void AboutMenu::updateTime()
{
    this->iTime = SDL_GetTicks();
}