#include "MenuOption.h"

MenuOption::MenuOption(std::string textToUSe, int iXPos, int iYPos)
{
    sText = textToUSe;
    pos = {iXPos, iYPos};
}

std::string MenuOption::getText()
{
    return sText;
}

void MenuOption::setText(std::string sText)
{
    this->sText = sText;
}

int MenuOption::getXPos() const
{
    return pos.x;
}

int MenuOption::getYPos() const
{
    return pos.y;
}