#pragma once

#include "IMG.h"
#include <ea_data_structures/ea_data_structures.h>

class Sprite
{
public:
    Sprite() = default;
    Sprite(SDL_Renderer* rR,
           const std::vector<std::string>& spritesToUse,
           const std::vector<unsigned int>& delaysToUse);

    void update();

    CIMG* getTexture();
    CIMG* getTexture(int iID);

private:
    EA::OwnedVector<CIMG> sprites;
    std::vector<unsigned int> delays;

    int currentFrame = 0;
    unsigned long timePassed = 0;
};
