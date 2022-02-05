#include "PauseMenu.h"
#include "Common/CFG.h"
#include "Common/Core.h"

/* ******************************************** */

PauseMenu::PauseMenu()
{
    rPause.x = 220;
    rPause.y = 140;
    rPause.w = 360;
    rPause.h = 142;

    lMO.createNew("RESUME", 0, 156);
    lMO.createNew("OPTIONS", 0, 180);
    lMO.createNew("QUIT TO MENU", 0, 228);
    lMO.createNew("QUIT TO DESKTOP", 0, 252);
}

void PauseMenu::draw(SDL_Renderer* rR)
{
    SDL_SetRenderDrawBlendMode(rR, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(rR, 4, 4, 4, 235);
    SDL_RenderFillRect(rR, &rPause);
    SDL_SetRenderDrawColor(rR, 255, 255, 255, 255);
    rPause.x += 1;
    rPause.y += 1;
    rPause.h -= 2;
    rPause.w -= 2;
    SDL_RenderDrawRect(rR, &rPause);
    rPause.x -= 1;
    rPause.y -= 1;
    rPause.h += 2;
    rPause.w += 2;

    for (int i = 0; i < lMO.size(); i++)
    {
        if (i == activeMenuOption)
        {
            getCFG().getText()->DrawCenterX(
                rR, lMO[i]->getText(), lMO[i]->getYPos(), 16, 255, 255, 255);
        }
        else
        {
            getCFG().getText()->DrawCenterX(
                rR, lMO[i]->getText(), lMO[i]->getYPos(), 16, 90, 90, 90);
        }
    }

    SDL_SetRenderDrawBlendMode(rR, SDL_BLENDMODE_NONE);
    CCore::getMap()->setBackgroundColor(rR);
}

/* ******************************************** */

void PauseMenu::enter()
{
    switch (activeMenuOption)
    {
        case 0:
            getCFG().getMM()->setViewID(Mario::MenuStates::Game);
            getCFG().getMusic()->playTrack();
            break;
        case 1:
            getCFG().getMM()->getOptions()->setEscapeToMainMenu(false);
            getCFG().getMM()->resetActiveOptionID(Mario::MenuStates::Options);
            getCFG().getMM()->getOptions()->updateVolumeRect();
            getCFG().getMM()->setViewID(Mario::MenuStates::Options);
            break;
        case 2:
            CCore::getMap()->resetGameData();
            getCFG().getMM()->setViewID(Mario::MenuStates::MainMenu);
            break;
        case 3:
            Mario::getGameState().quitGame = true;
            break;
    }
}

void PauseMenu::escape()
{
    getCFG().getMM()->setViewID(Mario::MenuStates::Game);
    getCFG().getMusic()->pauseTrack();
}

void PauseMenu::updateActiveButton(int iDir)
{
    Menu::updateActiveButton(iDir);
}