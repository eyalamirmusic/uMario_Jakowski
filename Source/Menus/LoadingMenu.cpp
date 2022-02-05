#include "LoadingMenu.h"
#include "Common/CFG.h"
#include "Common/Core.h"

void LoadingMenu::Update()
{
    if (SDL_GetTicks() >= iTime + 2500 + (loadingType ? 0 : 2750))
    {
        if (loadingType)
        {
            if (!CCore::getMap()->getInEvent())
            {
                CCore::getMap()->setSpawnPoint();
                CCore::getMap()->loadLVL();
            }
            getCFG().getMM()->setViewID(Mario::GameStates::eGame);
            getCFG().getMusic()->changeMusic(true, true);
        }
        else
        {
            CCore::getMap()->resetGameData();
            getCFG().getMM()->setViewID(Mario::GameStates::eMainMenu);
        }
    }
    else
    {
        getCFG().getMusic()->stopTrack();
    }
    CCore::getMap()->UpdateBlocks();
}

void LoadingMenu::Draw(SDL_Renderer* rR)
{
    if (loadingType)
    {
        CCore::getMap()->DrawGameLayout(rR);
        getCFG().getText()->Draw(rR, "WORLD", 320, 144);
        getCFG().getText()->Draw(rR, CCore::getMap()->getLevelName(), 416, 144);

        CCore::getMap()->getPlayer()->getMarioSprite()->getTexture()->Draw(
            rR, 342, 210 - CCore::getMap()->getPlayer()->getHitBoxY() / 2);

        getCFG().getText()->Draw(rR, "y", 384, 208);

        if (CCore::getMap()->getPlayer()->getNumOfLives() > 9)
        {
            CCore::getMap()->getBlock(180)->getSprite()->getTexture()->Draw(
                rR, 410, 210);
        }
        getCFG().getText()->Draw(
            rR,
            std::to_string(CCore::getMap()->getPlayer()->getNumOfLives()),
            432,
            208);
        getCFG().getText()->DrawCenterX(rR,
                                     "REMEMBER THAT YOU CAN RUN WITH "
                                         + getCFG().getKeyString(getCFG().keyIDShift),
                                     400,
                                     16);
    }
    else
    {
        CCore::getMap()->DrawGameLayout(rR);
        getCFG().getText()->DrawCenterX(rR, "GAME OVER", 240, 16);
    }
}

/* ******************************************** */

void LoadingMenu::updateTime()
{
    this->iTime = SDL_GetTicks();
}