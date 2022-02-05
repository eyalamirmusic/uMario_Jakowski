#include "Levels/Map.h"
#include "CommonHeader.h"

namespace Mario
{
struct GameState
{
    explicit GameState(SDL_Renderer* renderer);

    bool quitGame = false;
    EA::OwningPointer<Map> map;
};

extern GameState& getGameState(SDL_Renderer* renderer = nullptr);

} // namespace Mario
