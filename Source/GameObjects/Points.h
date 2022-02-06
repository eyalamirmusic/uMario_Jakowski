#pragma once

#include "CommonHeader.h"

class Points
{
public:
    Points(int x, int y, std::string textToUse, int width = 8, int height = 16);

    void Update();
    void Draw(SDL_Renderer* rR);

    bool getDelete() const;

private:
    juce::Rectangle<int> rect;
    int left = 96;

    std::string sText;
    bool shouldDelete = false;
};