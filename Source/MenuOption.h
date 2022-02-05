#pragma once

#include <string>

class MenuOption
{
private:
    std::string sText;
    int iXPos, iYPos;

public:
    MenuOption(std::string sText, int iXPos, int iYPos);
    ~MenuOption(void);

    std::string getText();
    void setText(std::string sText);

    int getXPos();
    int getYPos();
};