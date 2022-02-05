#pragma once

#include "Graphics/IMG.h"
#include "MainMenu.h"
#include "LoadingMenu.h"
#include "AboutMenu.h"
#include "Console.h"
#include "OptionsMenu.h"
#include "PauseMenu.h"


namespace Mario
{
enum class GameStates
{
    eMainMenu,
    eGameLoading,
    eGame,
    eAbout,
    eOptions,
    ePasue,
    //eLevelEditor,
};

class MenuManager
{
public:

    void Update();
    void Draw(SDL_Renderer* rR);

    void setBackgroundColor(SDL_Renderer* rR);

    void enter();
    void escape();
    void setKey(int keyID);
    void keyPressed(int iDir);

    void resetActiveOptionID(GameStates ID);

    GameStates getViewID() const;
    void setViewID(GameStates viewID);

    CIMG* getActiveOption();
    void setActiveOption(SDL_Renderer* rR);

    LoadingMenu* getLoadingMenu();
    AboutMenu* getAboutMenu();
    OptionsMenu* getOptions();

private:
    GameStates currentGameState = GameStates::eMainMenu;
    CIMG* activeOption;

    MainMenu oMainMenu;
    LoadingMenu oLoadingMenu;
    AboutMenu oAboutMenu;
    OptionsMenu oOptionsMenu;
    PauseMenu oPauseMenu;
    //Console* oConsole;
    //LevelEditor* oLE;
};
}

