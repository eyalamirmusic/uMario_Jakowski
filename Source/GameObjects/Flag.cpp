#include "Flag.h"
#include "Common/Core.h"

Flag::Flag(int iXPos, int iYPos)
    : pos(iXPos, iYPos)
{
    this->iYTextPos = getCFG().GAME_HEIGHT - 3 * 32;
    this->iPoints = -1;

    this->iBlockID =
        CCore::getMap()->getLevelType() == 4 || CCore::getMap()->getLevelType() == 3
            ? 168
            : 42;

    this->castleFlagExtraXPos = this->castleFlagY = 0;
}

void Flag::Update()
{
    pos.x += 4;
    iYTextPos -= 4;
}

void Flag::UpdateCastleFlag()
{
    if (castleFlagY <= 56)
        castleFlagY += 2;
}

void Flag::Draw(SDL_Renderer* rR, CIMG* iIMG)
{
    auto x = pos.x + (int) CCore::getMap()->getXPos();
    iIMG->draw(rR, x, pos.y);

    if (iPoints > 0)
    {
        getCFG().getText()->draw(
            rR, std::to_string(iPoints), x + 42, iYTextPos - 22, 8, 16);
    }
}

void Flag::DrawCastleFlag(SDL_Renderer* rR, CIMG* iIMG)
{
    auto mapX = (int) CCore::getMap()->getXPos();
    auto x = pos.x + mapX + castleFlagExtraXPos + 7 * 32 - 14;

    iIMG->draw(rR, x, getCFG().GAME_HEIGHT + 14 - 6 * 32 - castleFlagY);
}