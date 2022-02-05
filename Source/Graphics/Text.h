#pragma once

#include "CommonHeader.h"
#include "IMG.h"

class Text
{
public:
    Text();

    void draw(SDL_Renderer* rR, std::string sText, int X, int Y, int fontSize = 16);
    void draw(SDL_Renderer* rR,
              std::string sText,
              int X,
              int Y,
              int fontSize,
              int iR,
              int iG,
              int iB);
    void drawCenterX(SDL_Renderer* rR,
                     std::string sText,
                     int Y,
                     int fontSize = 16,
                     int iR = 255,
                     int iG = 255,
                     int iB = 255);
    void draw(
        SDL_Renderer* rR, std::string sText, int X, int Y, int iWidth, int iHeight);
    void drawWS(SDL_Renderer* rR,
                std::string sText,
                int X,
                int Y,
                int iR,
                int iG,
                int iB,
                int fontSize = 16);

    int getTextWidth(std::string sText, int fontSize = 16);

    void setFont(SDL_Renderer* rR, const std::string& fileName);

private:
    int getPos(int iChar);
    void checkExtra(int iChar);

    EA::OwningPointer<CIMG> font;

    SDL_Rect cropRect;
    SDL_Rect rect;

    int fontSize = 16;
    int extraLeft = 0;
    int nextExtraLeft = 0;
};