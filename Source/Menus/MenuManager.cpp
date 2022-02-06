#include "MenuManager.h"
#include "Common/Core.h"

namespace Mario
{
void MenuManager::update()
{
    auto* map = CCore::getMap();

    switch (currentGameState)
    {
        case MenuStates::MainMenu:
            oMainMenu.update();
            map->UpdateBlocks();
            break;

        case MenuStates::GameLoading:
            oLoadingMenu.update();
            break;

        case MenuStates::Game:
            map->Update();
            map->UpdateMinionsCollisions();
            break;

        case MenuStates::About:
            map->UpdateMinions();
            map->UpdateMinionBlokcs();
            map->UpdateBlocks();
            oAboutMenu.update();
            break;

        case MenuStates::Options:
            oOptionsMenu.update();
            break;

        case MenuStates::Pause:
            oPauseMenu.update();
            break;
    }
}

void MenuManager::draw(SDL_Renderer* rR)
{
    auto* map = CCore::getMap();

    switch (currentGameState)
    {
        case MenuStates::MainMenu:
            map->DrawMap(rR);
            map->getPlayer()->draw(rR);
            map->DrawGameLayout(rR);
            oMainMenu.draw(rR);
            break;

        case MenuStates::GameLoading:
            oLoadingMenu.draw(rR);
            break;

        case MenuStates::Game:
            map->Draw(rR);
            break;

        case MenuStates::About:
            map->DrawMap(rR);
            map->DrawMinions(rR);
            oAboutMenu.draw(rR);
            break;

        case MenuStates::Options:
            map->DrawMap(rR);
            map->DrawMinions(rR);
            map->getPlayer()->draw(rR);
            map->DrawGameLayout(rR);
            oOptionsMenu.draw(rR);
            break;

        case MenuStates::Pause:
            map->DrawMap(rR);
            map->DrawMinions(rR);
            map->getPlayer()->draw(rR);
            map->DrawGameLayout(rR);
            oPauseMenu.draw(rR);
            break;
    }
}

void MenuManager::setBackgroundColor(SDL_Renderer* rR)
{
    switch (currentGameState)
    {
        case MenuStates::MainMenu:
            CCore::getMap()->setBackgroundColor(rR);
            break;

        case MenuStates::GameLoading:
            SDL_SetRenderDrawColor(rR, 0, 0, 0, 255);
            break;

        case MenuStates::Game:
            CCore::getMap()->setBackgroundColor(rR);
            break;

        case MenuStates::About:
            oAboutMenu.setBackgroundColor(rR);
            break;

        case MenuStates::Options:
        case MenuStates::Pause:
            break;
    }
}

void MenuManager::enter()
{
    switch (currentGameState)
    {
        case MenuStates::MainMenu:
            oMainMenu.enter();
            break;

        case MenuStates::Game:
            CCore::getMap()->setDrawLines(!CCore::getMap()->getDrawLines());
            break;

        case MenuStates::About:
            oAboutMenu.enter();
            break;

        case MenuStates::Options:
            oOptionsMenu.enter();
            break;

        case MenuStates::Pause:
            oPauseMenu.enter();
            break;

        case MenuStates::GameLoading:
            break;
    }
}

void MenuManager::escape()
{
    switch (currentGameState)
    {
        case MenuStates::About:
            oAboutMenu.enter();
            break;

        case MenuStates::Options:
            oOptionsMenu.escape();
            break;

        case MenuStates::Pause:
            oPauseMenu.escape();
            break;

        case MenuStates::MainMenu:
            oMainMenu.escape();
            break;

        case MenuStates::Game:
        case MenuStates::GameLoading:
            break;
    }
}

void MenuManager::setKey(int keyID)
{
    switch (currentGameState)
    {
        case MenuStates::Options:
            oOptionsMenu.setKey(keyID);
            break;

        case MenuStates::MainMenu:
        case MenuStates::GameLoading:
        case MenuStates::Game:
        case MenuStates::About:
        case MenuStates::Pause:
            break;
    }
}

void MenuManager::keyPressed(int iDir)
{
    switch (currentGameState)
    {
        case MenuStates::MainMenu:
            oMainMenu.updateActiveButton(iDir);
            break;

        case MenuStates::Options:
            oOptionsMenu.updateActiveButton(iDir);
            break;

        case MenuStates::Pause:
            oPauseMenu.updateActiveButton(iDir);
            break;

        case MenuStates::GameLoading:
        case MenuStates::Game:
        case MenuStates::About:
            break;
    }
}

void MenuManager::resetActiveOptionID(MenuStates ID)
{
    switch (ID)
    {
        case MenuStates::MainMenu:
            oMainMenu.activeMenuOption = 0;
            break;

        case MenuStates::Options:
            oOptionsMenu.activeMenuOption = 0;
            break;

        case MenuStates::Pause:
            oPauseMenu.activeMenuOption = 0;
            break;

        case MenuStates::GameLoading:
        case MenuStates::Game:
        case MenuStates::About:
            break;
    }
}

MenuStates MenuManager::getViewID() const
{
    return currentGameState;
}

void MenuManager::setViewID(MenuStates viewID)
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
