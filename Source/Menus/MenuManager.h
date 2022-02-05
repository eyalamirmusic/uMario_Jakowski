#pragma once

#include "Graphics/IMG.h"
#include "MainMenu.h"
#include "LoadingMenu.h"
#include "AboutMenu.h"
#include "Console.h"
#include "OptionsMenu.h"
#include "PauseMenu.h"



class MenuManager
{
public:

    enum gameState
    {
        eMainMenu,
        eGameLoading,
        eGame,
        eAbout,
        eOptions,
        ePasue,
        //eLevelEditor,
    };

    gameState currentGameState = eMainMenu;

    void Update();
    void Draw(SDL_Renderer* rR);

    void setBackgroundColor(SDL_Renderer* rR);

    void enter();
    void escape();
    void setKey(int keyID);
    void keyPressed(int iDir);

    void resetActiveOptionID(gameState ID);

    int getViewID() const;
    void setViewID(gameState viewID);

    CIMG* getActiveOption();
    void setActiveOption(SDL_Renderer* rR);

    LoadingMenu* getLoadingMenu();
    AboutMenu* getAboutMenu();

    //Console* getConsole();
    //LevelEditor* getLE();
    OptionsMenu* getOptions();

private:
    CIMG* activeOption;

    MainMenu oMainMenu;
    LoadingMenu oLoadingMenu;
    AboutMenu oAboutMenu;
    OptionsMenu oOptionsMenu;
    PauseMenu oPauseMenu;
    //Console* oConsole;
    //LevelEditor* oLE;
};