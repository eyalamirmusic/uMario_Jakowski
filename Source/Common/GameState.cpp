#include "GameState.h"

namespace Mario
{
GameState& getGameState(SDL_Renderer* renderer)
{
    static EA::OwningPointer<GameState> state;

    if (state == nullptr)
    {
        state.create(renderer);
        state->map->loadLVL();
    }

    return *state;
}

GameState::GameState(SDL_Renderer* renderer)
{
    if (renderer == nullptr)
        quitGame = true;
    else
        map.create(renderer);
}
} // namespace Mario