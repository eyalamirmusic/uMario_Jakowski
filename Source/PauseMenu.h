#pragma once

#include "Menu.h"

class PauseMenu : public Menu
{
private:
    SDL_Rect rPause;

public:
    PauseMenu(void);
    ~PauseMenu(void);

    void Update();
    void Draw(SDL_Renderer* rR);

    void enter();
    void escape();

    void updateActiveButton(int iDir);
};