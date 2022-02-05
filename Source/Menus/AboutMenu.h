#pragma once

#include "Menu.h"

class AboutMenu : public Menu
{
public:
    AboutMenu();

    void update() override;
    void draw(SDL_Renderer* rR) override;

    void enter();

    void launch();
    void reset();

    void nextColor();
    int getColorStep(int iOld, int iNew);

    void setBackgroundColor(SDL_Renderer* rR);
    void updateTime();

private:
    unsigned int iTime = 0;

    int cR = 93;
    int cG = 148;
    int cB = 252;
    int nR = 0;
    int nG = 0;
    int nB = 0;
    int colorStepID = 1;
    int iColorID = 0;

    // ----- true = RIGHT, false = LEFT
    bool moveDirection = true;

    int iNumOfUnits = 0;

};