#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* rR,
               const std::vector<std::string>& spritesToUse,
               const std::vector<unsigned int>& delaysToUse)
    : delays(delaysToUse)
{
    for (auto& sprite: spritesToUse)
        sprites.createNew(sprite, rR);
}

void Sprite::update()
{
    if (SDL_GetTicks() - delays[currentFrame] > timePassed)
    {
        timePassed = SDL_GetTicks();

        if (currentFrame == sprites.getLastElementIndex())
            currentFrame = 0;
        else
            ++currentFrame;
    }
}

CIMG* Sprite::getTexture()
{
    return sprites[currentFrame];
}

CIMG* Sprite::getTexture(int iID)
{
    return sprites[iID];
}