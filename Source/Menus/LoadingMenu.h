#pragma once

#include "Menu.h"

class LoadingMenu : public Menu
{
public:
    void update() override;
    void draw(SDL_Renderer* rR) override;

    void updateTime();

    bool loadingType = true; // -- true = LOADING, false = GAME OVER

private:
    unsigned int iTime = 0;

};