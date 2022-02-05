#pragma once

#include "Levels/Map.h"


class CCore
{
public:
    CCore();
    ~CCore();

    void mainLoop();

    void Update();
    void Draw();

    void resetMove();
    static void resetKeys();
    static Map* getMap();

    static bool quitGame;
    static bool mouseLeftPressed, mouseRightPressed;
    static int mouseX, mouseY;

private:
    void Input();
    void MouseInput();
    void InputPlayer();
    void InputMenu();

    SDL_Window* window;
    SDL_Renderer* rR;
    SDL_Event* mainEvent;

    // ----- FPS -----

    long frameTime;
    static const int MIN_FRAME_TIME = 16;

    unsigned long lFPSTime;
    int iNumOfFPS, iFPS;

    // ----- FPS -----

    // ----- INPUT
    static bool movePressed, keyMenuPressed, keyS, keyW, keyA, keyD, keyShift;

    static bool keyAPressed, keyDPressed;
    // ----- true = RIGHT, false = LEFT
    bool firstDir;

    // ----- INPUT

    static Map* oMap;
};
