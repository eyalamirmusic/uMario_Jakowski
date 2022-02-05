#pragma once

#include "CommonHeader.h"
#include "Graphics/IMG.h"

class Bubble
{
private:
    int iXPos, iYPos;

    bool bDestoy; // -- DELETE BUBBLE
    int iBlockID;

public:
    Bubble(int iXPos, int iYPos);
    ~Bubble(void);

    void Update();
    void Draw(SDL_Renderer* rR, CIMG* iIMG);

    int getBlockID();
    bool getDestroy();
};