#include "MainMenu.h"
#include "Common/CFG.h"
#include "Common/Core.h"

MainMenu::MainMenu()
{
    lMO.createNew("1 Player GAME", 178, 276);
    lMO.createNew("OPTIONS", 222, 308);
    lMO.createNew("ABOUT", 237, 340);

    rSelectWorld.x = 122;
    rSelectWorld.y = 280;
    rSelectWorld.w = 306;
    rSelectWorld.h = 72;
}

void MainMenu::update()
{
    getCFG().getMusic()->stopTrack();

    Menu::update();
}

void MainMenu::draw(SDL_Renderer* rR)
{
    getCFG().getSMBLOGO()->draw(rR, 80, 48);
    Menu::draw(rR);
    getCFG().getText()->draw(
        rR, "WWW.LUKASZJAKOWSKI.PL", 4, getCFG().GAME_HEIGHT - 4 - 8, 8, 0, 0, 0);
    getCFG().getText()->draw(rR,
                             "WWW.LUKASZJAKOWSKI.PL",
                             5,
                             getCFG().GAME_HEIGHT - 5 - 8,
                             8,
                             255,
                             255,
                             255);

    if (selectWorld)
    {
        SDL_SetRenderDrawBlendMode(rR, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(rR, 4, 4, 4, 235);
        SDL_RenderFillRect(rR, &rSelectWorld);
        SDL_SetRenderDrawColor(rR, 255, 255, 255, 255);
        rSelectWorld.x += 1;
        rSelectWorld.y += 1;
        rSelectWorld.h -= 2;
        rSelectWorld.w -= 2;
        SDL_RenderDrawRect(rR, &rSelectWorld);
        rSelectWorld.x -= 1;
        rSelectWorld.y -= 1;
        rSelectWorld.h += 2;
        rSelectWorld.w += 2;

        getCFG().getText()->draw(
            rR,
            "SELECT WORLD",
            rSelectWorld.x + rSelectWorld.w / 2
                - getCFG().getText()->getTextWidth("SELECT WORLD") / 2,
            rSelectWorld.y + 16,
            16,
            255,
            255,
            255);

        for (int i = 0, extraX = 0; i < 8; i++)
        {
            if (i == activeWorldID)
            {
                getCFG().getText()->draw(
                    rR,
                    std::to_string(i + 1) + "-"
                        + std::to_string(activeSecondWorldID + 1),
                    rSelectWorld.x + 16 * (i + 1) + 16 * i + extraX,
                    rSelectWorld.y + 16 + 24,
                    16,
                    255,
                    255,
                    255);

                extraX = 32;

                /*for(int j = 0; j < 4; j++) {
                    if(j == activeSecondWorldID) {
                        getCFG().getText()->Draw(rR, std::to_string(j + 1), rSelectWorld.x + 16*(i + 1) + 16*i, rSelectWorld.y + 40 + 24*j, 16, 255, 255, 255);
                    } else {
                        getCFG().getText()->Draw(rR, std::to_string(j + 1), rSelectWorld.x + 16*(i + 1) + 16*i, rSelectWorld.y + 40 + 24*j, 16, 90, 90, 90);
                    }
                }*/
            }
            else
            {
                getCFG().getText()->draw(rR,
                                         std::to_string(i + 1),
                                         rSelectWorld.x + 16 * (i + 1) + 16 * i
                                             + extraX,
                                         rSelectWorld.y + 16 + 24,
                                         16,
                                         90,
                                         90,
                                         90);
            }
        }

        SDL_SetRenderDrawBlendMode(rR, SDL_BLENDMODE_NONE);
        CCore::getMap()->setBackgroundColor(rR);
    }
}

/* ******************************************** */

void MainMenu::enter()
{
    switch (activeMenuOption)
    {
        case 0:
            if (!selectWorld)
            {
                selectWorld = true;
            }
            else
            {
                getCFG().getMM()->getLoadingMenu()->updateTime();
                CCore::getMap()->resetGameData();
                CCore::getMap()->setCurrentLevelID(activeWorldID * 4
                                                   + activeSecondWorldID);
                getCFG().getMM()->setViewID(Mario::MenuStates::GameLoading);
                getCFG().getMM()->getLoadingMenu()->loadingType = true;
                CCore::getMap()->setSpawnPointID(0);
                selectWorld = false;
            }
            break;
        case 1:
            getCFG().getMM()->getOptions()->setEscapeToMainMenu(true);
            getCFG().getMM()->resetActiveOptionID(Mario::MenuStates::Options);
            getCFG().getMM()->getOptions()->updateVolumeRect();
            getCFG().getMM()->setViewID(Mario::MenuStates::Options);
            break;
        case 2:
            getCFG().getMM()->getAboutMenu()->updateTime();
            getCFG().getMM()->setViewID(Mario::MenuStates::About);
            getCFG().getMusic()->playTrack(Mario::Music::Tracks::Overworld);
            break;
    }
}

void MainMenu::escape()
{
    selectWorld = false;
}

void MainMenu::updateActiveButton(int iDir)
{
    switch (iDir)
    {
        case 0:
        case 2:
            if (!selectWorld)
            {
                Menu::updateActiveButton(iDir);
            }
            else
            {
                switch (iDir)
                {
                    case 0:
                        if (activeSecondWorldID < 1)
                        {
                            activeSecondWorldID = 3;
                        }
                        else
                        {
                            --activeSecondWorldID;
                        }
                        break;
                    case 2:
                        if (activeSecondWorldID > 2)
                        {
                            activeSecondWorldID = 0;
                        }
                        else
                        {
                            ++activeSecondWorldID;
                        }
                        break;
                }
            }
            break;
        case 1:
            if (selectWorld)
            {
                if (activeWorldID < 7)
                {
                    ++activeWorldID;
                }
                else
                {
                    activeWorldID = 0;
                }
            }
            break;
        case 3:
            if (selectWorld)
            {
                if (activeWorldID > 0)
                {
                    --activeWorldID;
                }
                else
                {
                    activeWorldID = 7;
                }
            }
            break;
    }
}