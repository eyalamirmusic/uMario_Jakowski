#pragma once

#include "CommonHeader.h"

class Points
{
public:
    Points(int x, int y, std::string textToUse, int width = 8, int height = 16);

    void update();
    void draw(SDL_Renderer* rR);

    bool getDelete() const;

private:
    EA::Rect<int> rect;
    int left = 96;

    std::string sText;
    bool shouldDelete = false;
};