#include "Coin.h"
#include "Common/Core.h"

Coin::Coin(int x, int y)
    : pos(x, y)
{
}

void Coin::update()
{
    if (iLEFT > 0)
    {
        iLEFT -= 5;
        pos.y = pos.y + (bTOP ? -5 : 5);

        ++iStepID;

        if (iStepID > 2)
        {
            iStepID = 0;
            ++iSpriteID;

            if (iSpriteID > 3)
            {
                iSpriteID = 0;
            }
        }
    }
    else if (bTOP)
    {
        bTOP = false;
        iLEFT = 80;
    }
    else
    {
        shouldDelete = true;
    }
}

void Coin::draw(SDL_Renderer* rR)
{
    auto texture = CCore::getMap()->getBlock(50)->getSprite()->getTexture(iSpriteID);

    auto x = pos.x + (int) CCore::getMap()->getXPos();
    texture->draw(rR, x, pos.y);
}

int Coin::getXPos()
{
    return pos.x;
}

int Coin::getYPos()
{
    return pos.y;
}

bool Coin::getDelete()
{
    return shouldDelete;
}