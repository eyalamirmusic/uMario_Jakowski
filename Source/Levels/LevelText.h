#pragma once

#include "CommonHeader.h"

class LevelText
{
public:
    LevelText(int x, int y, const std::string& textToUse);

    int getXPos() const;
    int getYPos() const;

    const std::string& getText();

private:
    EA::Point<int> pos;
    std::string sText;
};