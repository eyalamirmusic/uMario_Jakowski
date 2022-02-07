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

    long frameTime = 0;
    bool keyMenuPressed = false;
    bool keyS = false;
    bool keyShift = false;

    bool keyAPressed = false;
    bool keyDPressed = false;

    // ----- true = RIGHT, false = LEFT
    bool firstDir = false;
};
