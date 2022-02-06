#pragma once

#include <string>
#include "CommonHeader.h"

class MenuOption
{
public:
    MenuOption(std::string textToUse, int iXPos, int iYPos);

    std::string getText();
    void setText(std::string sText);

    int getXPos() const;
    int getYPos() const;

    EA::Point<int> getPos() const { return pos; }

private:
    std::string sText;
    EA::Point<int> pos;
};