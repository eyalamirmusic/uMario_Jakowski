#include "Points.h"

#include "Common/CFG.h"
#include "Common/Core.h"

Points::Points(int x, int y, std::string textToUse, int width, int height)
    : rect(x, y, width, height)
    , sText(std::move(textToUse))
{
}

void Points::Update()
{
    if (left > 0)
    {
        rect.y -= 2;
        left -= 2;
    }
    else
    {
        shouldDelete = true;
    }
}

void Points::Draw(SDL_Renderer* rR)
{
    auto x = rect.x + (int) CCore::getMap()->getXPos();

    getCFG().getText()->draw(
        rR, sText, x, rect.y, rect.w, rect.h);
}


bool Points::getDelete() const
{
    return shouldDelete;
}