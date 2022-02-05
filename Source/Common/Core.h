#pragma once

#include "GameState.h"

class CCore
{
public:
    CCore();
    ~CCore();

    void mainLoop();

    void update();
    void draw();

    void resetMove();
    static void resetKeys();
    static Map* getMap();

private:
    void input();
    void InputPlayer();
    void InputMenu();

    SDL_Window* window = nullptr;
    SDL_Renderer* rR = nullptr;
    SDL_Event* mainEvent = nullptr;

    // ----- FPS -----

    long frameTime = 0;

    unsigned long lFPSTime = 0;
    int iNumOfFPS = 0;
    int iFPS = 0;

    // ----- FPS -----

    bool movePressed = false;
    bool keyMenuPressed = false;
    bool keyS = false;
    bool keyW = false;
    bool keyA = false;
    bool keyD = false;
    bool keyShift = false;

    bool keyAPressed = false;
    bool keyDPressed = false;
    // ----- true = RIGHT, false = LEFT
    bool firstDir = false;
};
