#pragma once

#include "CommonHeader.h"
#include "Graphics/IMG.h"

class Bubble
{
public:
    Bubble(int x, int y);

    void update();
    void draw(SDL_Renderer* rR, CIMG* iIMG) const;

    int getBlockID() const;
    bool getDestroy() const;

private:
    EA::Point<int> pos;

    bool bDestoy = false; // -- DELETE BUBBLE
};