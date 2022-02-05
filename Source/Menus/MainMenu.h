#pragma once

#include "Menu.h"

class MainMenu : public Menu
{
public:
    MainMenu();

    void Update() override;
    void Draw(SDL_Renderer* rR) override;
    void updateActiveButton(int iDir) override;

    void enter();
    void escape();

private:
    bool selectWorld = false;
    int activeWorldID = 0;
    int activeSecondWorldID = 0;

    SDL_Rect rSelectWorld;

};