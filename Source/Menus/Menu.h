#pragma once

#include "CommonHeader.h"
#include "MenuOption.h"
#include <ea_data_structures/ea_data_structures.h>

class Menu
{
public:
    virtual ~Menu() = default;

    virtual void Update() {}
    virtual void Draw(SDL_Renderer* rR);

    // ----- 0 = TOP, 1 = RIGHT, 2 = BOTTOM, 3 = LEFT
    virtual void updateActiveButton(int iDir);

    int activeMenuOption = 0;

    EA::OwnedVector<MenuOption> lMO;
};