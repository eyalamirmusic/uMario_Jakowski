#pragma once

#include "Menu.h"

class LoadingMenu : public Menu
{
public:
    void Update() override;
    void Draw(SDL_Renderer* rR) override;

    void updateTime();

    bool loadingType = true; // -- true = LOADING, false = GAME OVER

private:
    unsigned int iTime = 0;

};