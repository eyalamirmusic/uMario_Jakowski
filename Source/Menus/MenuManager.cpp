#include "MenuManager.h"
#include "Common/Core.h"

namespace Mario
{
void MenuManager::Update()
{
    auto* map = CCore::getMap();

    switch (currentGameState)
    {
        case GameStates::eMainMenu:
            oMainMenu.Update();
            map->UpdateBlocks();
            break;

        case GameStates::eGameLoading:
            oLoadingMenu.Update();
            break;

        case GameStates::eGame:
            map->Update();
            map->UpdateMinionsCollisions();
            break;

        case GameStates::eAbout:
            map->UpdateMinions();
            map->UpdateMinionBlokcs();
            map->UpdateBlocks();
            oAboutMenu.Update();
            break;

        case GameStates::eOptions:
            oOptionsMenu.Update();
            break;

        case GameStates::ePasue:
            oPauseMenu.Update();
            break;
    }
}

void MenuManager::Draw(SDL_Renderer* rR)
{
    auto* map = CCore::getMap();

    switch (currentGameState)
    {
        case GameStates::eMainMenu:
            map->DrawMap(rR);
            map->getPlayer()->Draw(rR);
            map->DrawGameLayout(rR);
            oMainMenu.Draw(rR);
            break;

        case GameStates::eGameLoading:
            oLoadingMenu.Draw(rR);
            break;

        case GameStates::eGame:
            map->Draw(rR);
            break;

        case GameStates::eAbout:
            map->DrawMap(rR);
            map->DrawMinions(rR);
            oAboutMenu.Draw(rR);
            break;

        case GameStates::eOptions:
            map->DrawMap(rR);
            map->DrawMinions(rR);
            map->getPlayer()->Draw(rR);
            map->DrawGameLayout(rR);
            oOptionsMenu.Draw(rR);
            break;

        case GameStates::ePasue:
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
        case GameStates::eMainMenu:
            CCore::getMap()->setBackgroundColor(rR);
            break;

        case GameStates::eGameLoading:
            SDL_SetRenderDrawColor(rR, 0, 0, 0, 255);
            break;

        case GameStates::eGame:
            CCore::getMap()->setBackgroundColor(rR);
            break;

        case GameStates::eAbout:
            oAboutMenu.setBackgroundColor(rR);
            break;

        case GameStates::eOptions:
        case GameStates::ePasue:
            break;
    }
}

void MenuManager::enter()
{
    switch (currentGameState)
    {
        case GameStates::eMainMenu:
            oMainMenu.enter();
            break;

        case GameStates::eGame:
            CCore::getMap()->setDrawLines(!CCore::getMap()->getDrawLines());
            break;

        case GameStates::eAbout:
            oAboutMenu.enter();
            break;

        case GameStates::eOptions:
            oOptionsMenu.enter();
            break;

        case GameStates::ePasue:
            oPauseMenu.enter();
            break;

        case GameStates::eGameLoading:
            break;
    }
}

void MenuManager::escape()
{
    switch (currentGameState)
    {
        case GameStates::eAbout:
            oAboutMenu.enter();
            break;

        case GameStates::eOptions:
            oOptionsMenu.escape();
            break;

        case GameStates::ePasue:
            oPauseMenu.escape();
            break;

        case GameStates::eMainMenu:
            oMainMenu.escape();
            break;

        case GameStates::eGame:
        case GameStates::eGameLoading:
            break;
    }
}

void MenuManager::setKey(int keyID)
{
    switch (currentGameState)
    {
        case GameStates::eOptions:
            oOptionsMenu.setKey(keyID);
            break;

        case GameStates::eMainMenu:
        case GameStates::eGameLoading:
        case GameStates::eGame:
        case GameStates::eAbout:
        case GameStates::ePasue:
            break;
    }
}

void MenuManager::keyPressed(int iDir)
{
    switch (currentGameState)
    {
        case GameStates::eMainMenu:
            oMainMenu.updateActiveButton(iDir);
            break;

        case GameStates::eOptions:
            oOptionsMenu.updateActiveButton(iDir);
            break;

        case GameStates::ePasue:
            oPauseMenu.updateActiveButton(iDir);
            break;

        case GameStates::eGameLoading:
        case GameStates::eGame:
        case GameStates::eAbout:
            break;
    }
}

void MenuManager::resetActiveOptionID(GameStates ID)
{
    switch (ID)
    {
        case GameStates::eMainMenu:
            oMainMenu.activeMenuOption = 0;
            break;

        case GameStates::eOptions:
            oOptionsMenu.activeMenuOption = 0;
            break;

        case GameStates::ePasue:
            oPauseMenu.activeMenuOption = 0;
            break;

        case GameStates::eGameLoading:
        case GameStates::eGame:
        case GameStates::eAbout:
            break;
    }
}

GameStates MenuManager::getViewID() const
{
    return currentGameState;
}

void MenuManager::setViewID(GameStates viewID)
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
} // namespace Mario
