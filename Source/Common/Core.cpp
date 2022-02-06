#include "CommonHeader.h"
#include "Common/Core.h"
#include "CFG.h"

namespace Mario::Consts
{
constexpr int MIN_FRAME_TIME = 16;
} // namespace Mario::Consts

CCore::CCore()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);

    window = SDL_CreateWindow("uMario - www.LukaszJakowski.pl",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              getCFG().GAME_WIDTH,
                              getCFG().GAME_HEIGHT,
                              SDL_WINDOW_SHOWN);

    if (window != nullptr)
        rR = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // ----- ICO
    std::string fileName = "Resources/images/ico.bmp";
    SDL_Surface* loadedSurface = SDL_LoadBMP(fileName.c_str());
    SDL_SetColorKey(
        loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 0, 255));

    SDL_SetWindowIcon(window, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    mainEvent = new SDL_Event();
    // ----- ICO

    Mario::getGameState(rR);

    getCFG().getMM()->setActiveOption(rR);
    getCFG().getSMBLOGO()->setIMG("super_mario_bros", rR);
    getCFG().getMusic()->playTrack();

    getCFG().keyIDA = SDLK_a;
    getCFG().keyIDS = SDLK_s;
    getCFG().keyIDD = SDLK_d;
    getCFG().keyIDSpace = SDLK_SPACE;
    getCFG().keyIDShift = SDLK_LSHIFT;
}

CCore::~CCore()
{
    delete mainEvent;
    SDL_DestroyRenderer(rR);
    SDL_DestroyWindow(window);
}

void CCore::mainLoop()
{
    lFPSTime = SDL_GetTicks();

    while (!Mario::getGameState().quitGame && mainEvent->type != SDL_QUIT)
    {
        frameTime = SDL_GetTicks();
        SDL_PollEvent(mainEvent);
        SDL_RenderClear(rR);

        getCFG().getMM()->setBackgroundColor(rR);
        SDL_RenderFillRect(rR, nullptr);

        input();
        update();
        draw();

        SDL_RenderPresent(rR);

        if (SDL_GetTicks() - frameTime < Mario::Consts::MIN_FRAME_TIME)
        {
            SDL_Delay(Mario::Consts::MIN_FRAME_TIME - (SDL_GetTicks() - frameTime));
        }
    }
}

void CCore::input()
{
    if (getCFG().getMM()->getViewID() == Mario::MenuStates::Game)
    {
        if (!getMap()->getInEvent())
            InputPlayer();
        else
            resetMove();
    }
    else
        InputMenu();
}

void CCore::InputMenu()
{
    if (mainEvent->type == SDL_KEYDOWN)
    {
        getCFG().getMM()->setKey(mainEvent->key.keysym.sym);

        switch (mainEvent->key.keysym.sym)
        {
            case SDLK_s:
            case SDLK_DOWN:
                if (!keyMenuPressed)
                {
                    getCFG().getMM()->keyPressed(2);
                    keyMenuPressed = true;
                }
                break;
            case SDLK_w:
            case SDLK_UP:
                if (!keyMenuPressed)
                {
                    getCFG().getMM()->keyPressed(0);
                    keyMenuPressed = true;
                }
                break;
            case SDLK_KP_ENTER:
            case SDLK_RETURN:
                if (!keyMenuPressed)
                {
                    getCFG().getMM()->enter();
                    keyMenuPressed = true;
                }
                break;
            case SDLK_ESCAPE:
                if (!keyMenuPressed)
                {
                    getCFG().getMM()->escape();
                    keyMenuPressed = true;
                }
                break;
            case SDLK_LEFT:
            case SDLK_d:
                if (!keyMenuPressed)
                {
                    getCFG().getMM()->keyPressed(3);
                    keyMenuPressed = true;
                }
                break;
            case SDLK_RIGHT:
            case SDLK_a:
                if (!keyMenuPressed)
                {
                    getCFG().getMM()->keyPressed(1);
                    keyMenuPressed = true;
                }
                break;
        }
    }

    if (mainEvent->type == SDL_KEYUP)
    {
        switch (mainEvent->key.keysym.sym)
        {
            case SDLK_s:
            case SDLK_DOWN:
            case SDLK_w:
            case SDLK_UP:
            case SDLK_KP_ENTER:
            case SDLK_RETURN:
            case SDLK_ESCAPE:
            case SDLK_a:
            case SDLK_RIGHT:
            case SDLK_LEFT:
            case SDLK_d:
                keyMenuPressed = false;
                break;
            default:
                break;
        }
    }
}

void CCore::InputPlayer()
{
    if (mainEvent->type == SDL_WINDOWEVENT)
    {
        switch (mainEvent->window.event)
        {
            case SDL_WINDOWEVENT_FOCUS_LOST:
                getCFG().getMM()->resetActiveOptionID(Mario::MenuStates::Pause);
                getCFG().getMM()->setViewID(Mario::MenuStates::Pause);
                getCFG().getMusic()->playEffect(Mario::Music::Effects::Pause);
                getCFG().getMusic()->pauseTrack();
                break;
        }
    }

    auto* player = getMap()->getPlayer();

    if (mainEvent->type == SDL_KEYUP)
    {
        if (mainEvent->key.keysym.sym == getCFG().keyIDD)
        {
            if (firstDir)
            {
                firstDir = false;
            }

            keyDPressed = false;
        }

        if (mainEvent->key.keysym.sym == getCFG().keyIDS)
        {
            player->setSquat(false);
            keyS = false;
        }

        if (mainEvent->key.keysym.sym == getCFG().keyIDA)
        {
            if (!firstDir)
            {
                firstDir = true;
            }

            keyAPressed = false;
        }

        if (mainEvent->key.keysym.sym == getCFG().keyIDSpace)
        {
            getCFG().keySpace = false;
        }

        if (mainEvent->key.keysym.sym == getCFG().keyIDShift)
        {
            if (keyShift)
            {
                player->resetRun();
                keyShift = false;
            }
        }
        switch (mainEvent->key.keysym.sym)
        {
            case SDLK_KP_ENTER:
            case SDLK_RETURN:
            case SDLK_ESCAPE:
                keyMenuPressed = false;
                break;
        }
    }

    if (mainEvent->type == SDL_KEYDOWN)
    {
        if (mainEvent->key.keysym.sym == getCFG().keyIDD)
        {
            keyDPressed = true;
            if (!keyAPressed)
            {
                firstDir = true;
            }
        }

        if (mainEvent->key.keysym.sym == getCFG().keyIDS)
        {
            if (!keyS)
            {
                keyS = true;
                if (!getMap()->getUnderWater() && !player->getInLevelAnimation())
                    player->setSquat(true);
            }
        }

        if (mainEvent->key.keysym.sym == getCFG().keyIDA)
        {
            keyAPressed = true;
            if (!keyDPressed)
            {
                firstDir = false;
            }
        }

        if (mainEvent->key.keysym.sym == getCFG().keyIDSpace)
        {
            if (!getCFG().keySpace)
            {
                player->jump();
                getCFG().keySpace = true;
            }
        }

        if (mainEvent->key.keysym.sym == getCFG().keyIDShift)
        {
            if (!keyShift)
            {
                player->startRun();
                keyShift = true;
            }
        }

        switch (mainEvent->key.keysym.sym)
        {
            case SDLK_KP_ENTER:
            case SDLK_RETURN:
                if (!keyMenuPressed)
                {
                    getCFG().getMM()->enter();
                    keyMenuPressed = true;
                }
            case SDLK_ESCAPE:
                if (!keyMenuPressed
                    && getCFG().getMM()->getViewID() == Mario::MenuStates::Game)
                {
                    getCFG().getMM()->resetActiveOptionID(Mario::MenuStates::Pause);
                    getCFG().getMM()->setViewID(Mario::MenuStates::Pause);
                    getCFG().getMusic()->playEffect(Mario::Music::Effects::Pause);
                    getCFG().getMusic()->pauseTrack();
                    keyMenuPressed = true;
                }
                break;
        }
    }

    if (keyAPressed)
    {
        if (!player->getMove() && firstDir == false
            && !player->getChangeMoveDirection() && !player->getSquat())
        {
            player->startMove();
            player->setMoveDirection(false);
        }
        else if (!keyDPressed && player->getMoveSpeed() > 0
                 && firstDir != player->getMoveDirection())
        {
            player->setChangeMoveDirection();
        }
    }

    if (keyDPressed)
    {
        if (!player->getMove() && firstDir == true
            && !player->getChangeMoveDirection() && !player->getSquat())
        {
            player->startMove();
            player->setMoveDirection(true);
        }
        else if (!keyAPressed && player->getMoveSpeed() > 0
                 && firstDir != player->getMoveDirection())
        {
            player->setChangeMoveDirection();
        }
    }

    if (player->getMove() && !keyAPressed && !keyDPressed)
    {
        player->resetMove();
    }
}

void CCore::resetKeys()
{
    //This static function used to be here to reset the keys.
    //It's probably wrong to have it statically available like that so I'm keeping
    //it here until I know why it was created

    assert(false);
    //    movePressed = keyMenuPressed = keyS = keyW = keyA = keyD = getCFG().keySpace =
    //        keyShift = keyAPressed = keyDPressed = false;
}

void CCore::update()
{
    getCFG().getMM()->update();
}

void CCore::draw()
{
    getCFG().getMM()->draw(rR);
}

void CCore::resetMove()
{
    keyAPressed = keyDPressed = false;
}

Map* CCore::getMap()
{
    return Mario::getGameState().map;
}