#include "IMG.h"


CIMG::CIMG(const std::string& fileName, SDL_Renderer* rR)
{
    setIMG(fileName, rR);
}

CIMG::~CIMG()
{
    SDL_DestroyTexture(tIMG);
}

/* ******************************************** */

void CIMG::draw(SDL_Renderer* rR, int iXOffset, int iYOffset)
{
    rRect.x = iXOffset;
    rRect.y = iYOffset;

    SDL_RenderCopy(rR, tIMG, nullptr, &rRect);
}

void CIMG::draw(SDL_Renderer* rR, int iXOffset, int iYOffset, bool bRoate)
{
    rRect.x = iXOffset;
    rRect.y = iYOffset;

    if (!bRoate)
    {
        SDL_RenderCopy(rR, tIMG, nullptr, &rRect);
    }
    else
    {
        SDL_RenderCopyEx(rR, tIMG, nullptr, &rRect, 180.0, nullptr, SDL_FLIP_VERTICAL);
    }
}

void CIMG::drawVert(SDL_Renderer* rR, int iXOffset, int iYOffset)
{
    rRect.x = iXOffset;
    rRect.y = iYOffset;

    SDL_RenderCopyEx(rR, tIMG, nullptr, &rRect, 180.0, nullptr, SDL_FLIP_HORIZONTAL);
}

void CIMG::draw(SDL_Renderer* rR, SDL_Rect rCrop, SDL_Rect rRect)
{
    SDL_RenderCopy(rR, tIMG, &rCrop, &rRect);
}

void CIMG::setIMG(std::string fileName, SDL_Renderer* rR)
{

    fileName = "files/images/" + fileName + ".bmp";
    SDL_Surface* loadedSurface = SDL_LoadBMP(fileName.c_str());
    SDL_SetColorKey(
        loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 0, 255));

    tIMG = SDL_CreateTextureFromSurface(rR, loadedSurface);
    int iWidth, iHeight;

    SDL_QueryTexture(tIMG, nullptr, nullptr, &iWidth, &iHeight);

    rRect.x = 0;
    rRect.y = 0;
    rRect.w = iWidth;
    rRect.h = iHeight;
    SDL_FreeSurface(loadedSurface);
}

SDL_Texture* CIMG::getIMG()
{
    return tIMG;
}
