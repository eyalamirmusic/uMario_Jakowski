#pragma once

#include "CommonHeader.h"

class CIMG
{
public:
    CIMG() = default;
    CIMG(const std::string& fileName, SDL_Renderer* rR);

    ~CIMG();

    void draw(SDL_Renderer* rR, int iXOffset, int iYOffset);
    void draw(SDL_Renderer* rR, int iXOffset, int iYOffset, bool bRoate);
    void drawVert(SDL_Renderer* rR, int iXOffset, int iYOffset);
    void draw(SDL_Renderer* rR, SDL_Rect rCrop, SDL_Rect rRect);

    /* ----- get & set ----- */
    SDL_Texture* getIMG();
    void setIMG(std::string fileName, SDL_Renderer* rR);

private:
    SDL_Texture* tIMG = nullptr;
    SDL_Rect rRect {};
};
