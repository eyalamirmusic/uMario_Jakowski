#pragma once

#include "Graphics/IMG.h"
#include "MainMenu.h"
#include "LoadingMenu.h"
#include "AboutMenu.h"
#include "OptionsMenu.h"
#include "PauseMenu.h"


namespace Mario
{
enum class MenuStates
{
    MainMenu,
    GameLoading,
    Game,
    About,
    Options,
    Pause
};

class MenuManager
{
public:

    void update();
    void draw(SDL_Renderer* rR);

    void setBackgroundColor(SDL_Renderer* rR);

    void enter();
    void escape();
    void setKey(int keyID);
    void keyPressed(int iDir);

    void resetActiveOptionID(MenuStates ID);

    MenuStates getViewID() const;
    void setViewID(MenuStates viewID);

    CIMG* getActiveOption();
    void setActiveOption(SDL_Renderer* rR);

    LoadingMenu* getLoadingMenu();
    AboutMenu* getAboutMenu();
    OptionsMenu* getOptions();

private:
    MenuStates currentGameState = MenuStates::MainMenu;
    CIMG* activeOption = nullptr;

    MainMenu oMainMenu;
    LoadingMenu oLoadingMenu;
    AboutMenu oAboutMenu;
    OptionsMenu oOptionsMenu;
    PauseMenu oPauseMenu;
    //Console* oConsole;
    //LevelEditor* oLE;
};
}

