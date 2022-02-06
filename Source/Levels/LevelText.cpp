#include "LevelText.h"

LevelText::LevelText(int x, int y, const std::string& textToUse)
    : pos(x, y)
    , sText(textToUse)
{
}

int LevelText::getXPos() const
{
    return pos.x;
}

int LevelText::getYPos() const
{
    return pos.y;
}

const std::string& LevelText::getText()
{
    return sText;
}