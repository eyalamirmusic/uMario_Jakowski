#include "CommonHeader.h"
#include "Common/Core.h"
#include "CFG.h"
#include "SDL_mixer.h"

CCore::CCore()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);

    window = SDL_CreateWindow("uMario - www.LukaszJakowski.pl",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              CCFG::GAME_WIDTH,
                              CCFG::GAME_HEIGHT,
                              SDL_WINDOW_SHOWN);

    if (window != nullptr)
        rR = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // ----- ICO
    std::string fileName = "files/images/ico.bmp";
    SDL_Surface* loadedSurface = SDL_LoadBMP(fileName.c_str());
    SDL_SetColorKey(
        loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 0, 255));

    SDL_SetWindowIcon(window, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    mainEvent = new SDL_Event();
    // ----- ICO

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    Mario::getGameState(rR);

    CCFG::getMM()->setActiveOption(rR);
    CCFG::getSMBLOGO()->setIMG("super_mario_bros", rR);
    CCFG::getMusic()->playTrack();

    CCFG::keyIDA = SDLK_a;
    CCFG::keyIDS = SDLK_s;
    CCFG::keyIDD = SDLK_d;
    CCFG::keyIDSpace = SDLK_SPACE;
    CCFG::keyIDShift = SDLK_LSHIFT;
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

        CCFG::getMM()->setBackgroundColor(rR);
        SDL_RenderFillRect(rR, nullptr);

        Input();
        update();
        draw();

        SDL_RenderPresent(rR);

        if (SDL_GetTicks() - frameTime < Consts::MIN_FRAME_TIME)
        {
            SDL_Delay(Consts::MIN_FRAME_TIME - (SDL_GetTicks() - frameTime));
        }
    }
}

void CCore::Input()
{
    switch (CCFG::getMM()->getViewID())
    {
        case 2:
        case 7:
            if (!getMap()->getInEvent())
            {
                InputPlayer();
            }
            else
            {
                resetMove();
            }
            break;
        default:
            InputMenu();
            break;
    }
}

void CCore::InputMenu()
{
    if (mainEvent->type == SDL_KEYDOWN)
    {
        CCFG::getMM()->setKey(mainEvent->key.keysym.sym);

        switch (mainEvent->key.keysym.sym)
        {
            case SDLK_s:
            case SDLK_DOWN:
                if (!keyMenuPressed)
                {
                    CCFG::getMM()->keyPressed(2);
                    keyMenuPressed = true;
                }
                break;
            case SDLK_w:
            case SDLK_UP:
                if (!keyMenuPressed)
                {
                    CCFG::getMM()->keyPressed(0);
                    keyMenuPressed = true;
                }
                break;
            case SDLK_KP_ENTER:
            case SDLK_RETURN:
                if (!keyMenuPressed)
                {
                    CCFG::getMM()->enter();
                    keyMenuPressed = true;
                }
                break;
            case SDLK_ESCAPE:
                if (!keyMenuPressed)
                {
                    CCFG::getMM()->escape();
                    keyMenuPressed = true;
                }
                break;
            case SDLK_LEFT:
            case SDLK_d:
                if (!keyMenuPressed)
                {
                    CCFG::getMM()->keyPressed(3);
                    keyMenuPressed = true;
                }
                break;
            case SDLK_RIGHT:
            case SDLK_a:
                if (!keyMenuPressed)
                {
                    CCFG::getMM()->keyPressed(1);
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
                CCFG::getMM()->resetActiveOptionID(CCFG::getMM()->ePasue);
                CCFG::getMM()->setViewID(CCFG::getMM()->ePasue);
                CCFG::getMusic()->playEffect(Mario::Music::Effects::Pause);
                CCFG::getMusic()->pauseTrack();
                break;
        }
    }

    auto* player = getMap()->getPlayer();

    if (mainEvent->type == SDL_KEYUP)
    {
        if (mainEvent->key.keysym.sym == CCFG::keyIDD)
        {
            if (firstDir)
            {
                firstDir = false;
            }

            keyDPressed = false;
        }

        if (mainEvent->key.keysym.sym == CCFG::keyIDS)
        {
            player->setSquat(false);
            keyS = false;
        }

        if (mainEvent->key.keysym.sym == CCFG::keyIDA)
        {
            if (!firstDir)
            {
                firstDir = true;
            }

            keyAPressed = false;
        }

        if (mainEvent->key.keysym.sym == CCFG::keyIDSpace)
        {
            CCFG::keySpace = false;
        }

        if (mainEvent->key.keysym.sym == CCFG::keyIDShift)
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
        if (mainEvent->key.keysym.sym == CCFG::keyIDD)
        {
            keyDPressed = true;
            if (!keyAPressed)
            {
                firstDir = true;
            }
        }

        if (mainEvent->key.keysym.sym == CCFG::keyIDS)
        {
            if (!keyS)
            {
                keyS = true;
                if (!getMap()->getUnderWater() && !player->getInLevelAnimation())
                    player->setSquat(true);
            }
        }

        if (mainEvent->key.keysym.sym == CCFG::keyIDA)
        {
            keyAPressed = true;
            if (!keyDPressed)
            {
                firstDir = false;
            }
        }

        if (mainEvent->key.keysym.sym == CCFG::keyIDSpace)
        {
            if (!CCFG::keySpace)
            {
                player->jump();
                CCFG::keySpace = true;
            }
        }

        if (mainEvent->key.keysym.sym == CCFG::keyIDShift)
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
                    CCFG::getMM()->enter();
                    keyMenuPressed = true;
                }
            case SDLK_ESCAPE:
                if (!keyMenuPressed
                    && CCFG::getMM()->getViewID() == CCFG::getMM()->eGame)
                {
                    CCFG::getMM()->resetActiveOptionID(CCFG::getMM()->ePasue);
                    CCFG::getMM()->setViewID(CCFG::getMM()->ePasue);
                    CCFG::getMusic()->playEffect(Mario::Music::Effects::Pause);
                    CCFG::getMusic()->pauseTrack();
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

    jassertfalse;
    //    movePressed = keyMenuPressed = keyS = keyW = keyA = keyD = CCFG::keySpace =
    //        keyShift = keyAPressed = keyDPressed = false;
}

void CCore::update()
{
    CCFG::getMM()->Update();
}

void CCore::draw()
{
    CCFG::getMM()->Draw(rR);
}

void CCore::resetMove()
{
    keyAPressed = keyDPressed = false;
}

Map* CCore::getMap()
{
    return Mario::getGameState().map;
}

Mario::GameState& Mario::getGameState(SDL_Renderer* renderer)
{
    static EA::OwningPointer<GameState> state;

    if (state == nullptr)
    {
        state.create(renderer);
        state->map->loadLVL();
    }

    return *state;
}
