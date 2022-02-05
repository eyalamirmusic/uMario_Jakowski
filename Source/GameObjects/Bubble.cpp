#include "Bubble.h"
#include "Common/Core.h"
#include "Common/CFG.h"

/* ******************************************** */

Bubble::Bubble(int iXPos, int iYPos)
{
    this->iXPos = iXPos;
    this->iYPos = iYPos;

    this->bDestoy = false;

    this->iBlockID = 96;
}

Bubble::~Bubble(void)
{
}

/* ******************************************** */

void Bubble::Update()
{
    if (iYPos < getCFG().GAME_HEIGHT - 12 * 32 - 8)
    {
        bDestoy = true;
    }
    else
    {
        iYPos -= 1;
    }
}

void Bubble::Draw(SDL_Renderer* rR, CIMG* iIMG)
{
    iIMG->Draw(rR, (int) (iXPos + CCore::getMap()->getXPos()), iYPos);
}

/* ******************************************** */

int Bubble::getBlockID()
{
    return iBlockID;
}

bool Bubble::getDestroy()
{
    return bDestoy;
}