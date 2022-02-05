#include "MenuManager.h"
#include "Common/Core.h"

void MenuManager::Update()
{
    auto* map = CCore::getMap();

    switch (currentGameState)
    {
        case eMainMenu:
            oMainMenu.Update();
            map->UpdateBlocks();
            break;

        case eGameLoading:
            oLoadingMenu.Update();
            break;

        case eGame:
            map->Update();
            map->UpdateMinionsCollisions();
            break;

        case eAbout:
            map->UpdateMinions();
            map->UpdateMinionBlokcs();
            map->UpdateBlocks();
            oAboutMenu.Update();
            break;

        case eOptions:
            oOptionsMenu.Update();
            break;

        case ePasue:
            oPauseMenu.Update();
            break;
    }
}

void MenuManager::Draw(SDL_Renderer* rR)
{
    auto* map = CCore::getMap();

    switch (currentGameState)
    {
        case eMainMenu:
            map->DrawMap(rR);
            map->getPlayer()->Draw(rR);
            map->DrawGameLayout(rR);
            oMainMenu.Draw(rR);
            break;

        case eGameLoading:
            oLoadingMenu.Draw(rR);
            break;

        case eGame:
            map->Draw(rR);
            break;

        case eAbout:
            map->DrawMap(rR);
            map->DrawMinions(rR);
            oAboutMenu.Draw(rR);
            break;

        case eOptions:
            map->DrawMap(rR);
            map->DrawMinions(rR);
            map->getPlayer()->Draw(rR);
            map->DrawGameLayout(rR);
            oOptionsMenu.Draw(rR);
            break;

        case ePasue:
            map->DrawMap(rR);
            map->DrawMinions(rR);
            map->getPlayer()->Draw(rR);
            map->DrawGameLayout(rR);
            oPauseMenu.Draw(rR);
            break;
    }
}

void MenuManager::setBackgroundColor(SDL_Renderer* rR)
{
    switch (currentGameState)
    {
        case eMainMenu:
            CCore::getMap()->setBackgroundColor(rR);
            break;

        case eGameLoading:
            SDL_SetRenderDrawColor(rR, 0, 0, 0, 255);
            break;

        case eGame:
            CCore::getMap()->setBackgroundColor(rR);
            break;

        case eAbout:
            oAboutMenu.setBackgroundColor(rR);
            break;

        case eOptions:
        case ePasue:
            break;
    }
}

void MenuManager::enter()
{
    switch (currentGameState)
    {
        case eMainMenu:
            oMainMenu.enter();
            break;

        case eGame:
            CCore::getMap()->setDrawLines(!CCore::getMap()->getDrawLines());
            break;

        case eAbout:
            oAboutMenu.enter();
            break;

        case eOptions:
            oOptionsMenu.enter();
            break;

        case ePasue:
            oPauseMenu.enter();
            break;

        case eGameLoading:
            break;
    }
}

void MenuManager::escape()
{
    switch (currentGameState)
    {
        case eAbout:
            oAboutMenu.enter();
            break;

        case eOptions:
            oOptionsMenu.escape();
            break;

        case ePasue:
            oPauseMenu.escape();
            break;

        case eMainMenu:
            oMainMenu.escape();
            break;

        case eGame:
        case eGameLoading:
            break;
    }
}

void MenuManager::setKey(int keyID)
{
    switch (currentGameState)
    {
        case eOptions:
            oOptionsMenu.setKey(keyID);
            break;

        case eMainMenu:
        case eGameLoading:
        case eGame:
        case eAbout:
        case ePasue:
            break;
    }
}

void MenuManager::keyPressed(int iDir)
{
    switch (currentGameState)
    {
        case eMainMenu:
            oMainMenu.updateActiveButton(iDir);
            break;

        case eOptions:
            oOptionsMenu.updateActiveButton(iDir);
            break;

        case ePasue:
            oPauseMenu.updateActiveButton(iDir);
            break;

        case eGameLoading:
        case eGame:
        case eAbout:
            break;
    }
}

void MenuManager::resetActiveOptionID(gameState ID)
{
    switch (ID)
    {
        case eMainMenu:
            oMainMenu.activeMenuOption = 0;
            break;

        case eOptions:
            oOptionsMenu.activeMenuOption = 0;
            break;

        case ePasue:
            oPauseMenu.activeMenuOption = 0;
            break;

        case eGameLoading:
        case eGame:
        case eAbout:
            break;
    }
}

int MenuManager::getViewID() const
{
    return currentGameState;
}

void MenuManager::setViewID(gameState viewID)
{
    currentGameState = viewID;
}

CIMG* MenuManager::getActiveOption()
{
    return activeOption;
}

void MenuManager::setActiveOption(SDL_Renderer* rR)
{
    activeOption = new CIMG("active_option", rR);
}

LoadingMenu* MenuManager::getLoadingMenu()
{
    return &oLoadingMenu;
}

AboutMenu* MenuManager::getAboutMenu()
{
    return &oAboutMenu;
}

OptionsMenu* MenuManager::getOptions()
{
    return &oOptionsMenu;
}