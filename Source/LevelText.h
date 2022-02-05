#pragma once

#include <string>

class LevelText
{
private:
    int iXPos, iYPos;

    std::string sText;

public:
    LevelText(int iXPos, int iYPos, std::string sText);
    ~LevelText(void);

    int getXPos();
    int getYPos();
    std::string getText();
    void setText(std::string sText);
};