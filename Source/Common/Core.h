#pragma once

#include "Levels/Map.h"
#include "CommonHeader.h"



namespace Mario
{
struct GameState
{
    explicit GameState(SDL_Renderer* renderer)
    {
        if (renderer == nullptr)
            quitGame = true;
        else
            map.create(renderer);
    }

    bool quitGame = false;
    EA::OwningPointer<Map> map;
};

extern GameState& getGameState(SDL_Renderer* renderer = nullptr);

} // namespace Mario

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
    void Input();
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
