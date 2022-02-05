#pragma once

#include "Menu.h"

class OptionsMenu : public Menu
{
public:
    OptionsMenu();

    void update() override;
    void draw(SDL_Renderer* rR) override;
    void updateActiveButton(int iDir) override;

    void enter();
    void escape();
    void setKey(int keyID);

    void updateVolumeRect();

    void setEscapeToMainMenu(bool escapeToMainMenu);

private:
    SDL_Rect rRect;
    SDL_Rect rSetKeyRect;
    SDL_Rect rVolumeBG;
    SDL_Rect rVolume;

    bool inSetKey = false;
    bool resetSetKey = false;

    bool escapeToMainMenu = true;
};