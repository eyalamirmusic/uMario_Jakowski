#pragma once

#include "Menu.h"

class PauseMenu : public Menu
{
public:
    PauseMenu();

    void draw(SDL_Renderer* rR) override;

    void enter();
    void escape();

    void updateActiveButton(int iDir) override;

private:
    SDL_Rect rPause;

};