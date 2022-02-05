#include "Menu.h"
#include "Common/CFG.h"

void Menu::draw(SDL_Renderer* rR)
{
    for (auto& i: lMO)
    {
        getCFG().getText()->draw(rR, i->getText(), i->getXPos(), i->getYPos());
    }

    getCFG().getMM()->getActiveOption()->draw(
        rR, lMO[activeMenuOption]->getXPos() - 32, lMO[activeMenuOption]->getYPos());
}

void Menu::updateActiveButton(int iDir)
{
    switch (iDir)
    {
        case 0:
            if (activeMenuOption - 1 < 0)
                activeMenuOption = lMO.getLastElementIndex();
            else
                --activeMenuOption;

            break;

        case 2:
            if (activeMenuOption >= lMO.getLastElementIndex())
                activeMenuOption = 0;
            else
                ++activeMenuOption;
            break;

        default:
            break;
    }
}