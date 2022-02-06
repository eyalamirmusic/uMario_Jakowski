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
        rect.setY(rect.getY() - 2);
        left -= 2;
    }
    else
    {
        shouldDelete = true;
    }
}

void Points::Draw(SDL_Renderer* rR)
{
    auto x = rect.getX() + (int) CCore::getMap()->getXPos();

    getCFG().getText()->draw(
        rR, sText, x, rect.getY(), rect.getWidth(), rect.getHeight());
}


bool Points::getDelete() const
{
    return shouldDelete;
}