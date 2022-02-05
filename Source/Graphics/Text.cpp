#include "Text.h"
#include "Common/CFG.h"

Text::Text()
{
    cropRect.x = 0;
    cropRect.y = 0;
    cropRect.w = 8;
    cropRect.h = 8;

    rect.x = 0;
    rect.y = 0;
    rect.w = 16;
    rect.h = 16;
}

void Text::draw(SDL_Renderer* rR, std::string sText, int X, int Y, int fontSize)
{
    this->fontSize = fontSize;
    this->extraLeft = 0;
    this->nextExtraLeft = 0;

    for (unsigned int i = 0; i < sText.size(); i++)
    {
        cropRect.x = getPos(sText.at(i));

        rect.x = X + fontSize * i - extraLeft;
        rect.y = Y;
        rect.w = fontSize;
        rect.h = fontSize;
        font->draw(rR, cropRect, rect);
        extraLeft += nextExtraLeft;
        nextExtraLeft = 0;
    }
}

void Text::draw(SDL_Renderer* rR,
                std::string sText,
                int X,
                int Y,
                int fontSize,
                int iR,
                int iG,
                int iB)
{
    this->fontSize = fontSize;
    this->extraLeft = 0;
    this->nextExtraLeft = 0;

    for (unsigned int i = 0; i < sText.size(); i++)
    {
        SDL_SetTextureColorMod(font->getIMG(), iR, iG, iB);
        cropRect.x = getPos(sText.at(i));

        rect.x = X + fontSize * i - extraLeft;
        rect.y = Y;
        rect.w = fontSize;
        rect.h = fontSize;
        font->draw(rR, cropRect, rect);
        extraLeft += nextExtraLeft;
        nextExtraLeft = 0;
        SDL_SetTextureColorMod(font->getIMG(), 255, 255, 255);
    }
}

void Text::drawCenterX(
    SDL_Renderer* rR, std::string sText, int Y, int fontSize, int iR, int iG, int iB)
{
    int X = getCFG().GAME_WIDTH / 2 - getTextWidth(sText, fontSize) / 2;

    draw(rR, sText, X, Y, fontSize, iR, iG, iB);
}

void Text::draw(
    SDL_Renderer* rR, std::string sText, int X, int Y, int iWidth, int iHeight)
{
    for (unsigned int i = 0; i < sText.size(); i++)
    {
        cropRect.x = getPos(sText.at(i));

        rect.x = X + iWidth * i - extraLeft;
        rect.y = Y;
        rect.w = iWidth;
        rect.h = iHeight;
        font->draw(rR, cropRect, rect);
    }
}

void Text::drawWS(SDL_Renderer* rR,
                  std::string sText,
                  int X,
                  int Y,
                  int iR,
                  int iG,
                  int iB,
                  int fontSize)
{
    this->fontSize = fontSize;
    this->extraLeft = 0;
    this->nextExtraLeft = 0;

    for (unsigned int i = 0; i < sText.size(); i++)
    {
        SDL_SetTextureColorMod(font->getIMG(), 0, 0, 0);
        cropRect.x = getPos(sText.at(i));

        rect.x = X + fontSize * i - extraLeft - 1;
        rect.y = Y + 1;
        rect.w = fontSize;
        rect.h = fontSize;
        font->draw(rR, cropRect, rect);
        SDL_SetTextureColorMod(font->getIMG(), 255, 255, 255);
        rect.x = X + fontSize * i - extraLeft + 1;
        rect.y = Y - 1;
        font->draw(rR, cropRect, rect);
        extraLeft += nextExtraLeft;
        nextExtraLeft = 0;
    }
}

int Text::getTextWidth(std::string sText, int fontSize)
{
    int iOutput = (int)sText.size() * fontSize;
    nextExtraLeft = 0;

    for (char i: sText)
        checkExtra(i);

    iOutput -= nextExtraLeft;

    return iOutput;
}

int Text::getPos(int iChar)
{
    if (iChar >= 43 && iChar < 91)
    {
        checkExtra(iChar);
        return (iChar - 43) * cropRect.w + cropRect.w;
    }

    if (iChar >= 118 && iChar < 123)
    { // v w x y z
        return (iChar - 70) * cropRect.w + cropRect.w;
    }

    return 0;
}

void Text::checkExtra(int iChar)
{
    switch (iChar)
    {
        case 44:
        case 46:
        case 58:
        case 59:
            nextExtraLeft += 4 * fontSize / rect.w;
            break;
        default:
            break;
    }
}

/* ******************************************** */

void Text::setFont(SDL_Renderer* rR, const std::string& fileName)
{
    font.create(fileName, rR);
}