#include "Bubble.h"
#include "Common/Core.h"
#include "Common/CFG.h"

Bubble::Bubble(int x, int y)
    : pos(x, y)
{
}
void Bubble::update()
{
    if (pos.y < getCFG().GAME_HEIGHT - 12 * 32 - 8)
        bDestoy = true;
    else
        pos.y -= 1;
}

void Bubble::draw(SDL_Renderer* rR, CIMG* iIMG) const
{
    auto x = pos.x + (int) CCore::getMap()->getXPos();
    iIMG->draw(rR, x, pos.y);
}

int Bubble::getBlockID() const
{
    return 96;
}

bool Bubble::getDestroy() const
{
    return bDestoy;
}