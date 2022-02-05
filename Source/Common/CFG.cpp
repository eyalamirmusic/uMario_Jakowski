#include "CFG.h"

namespace Mario
{
Text* CCFG::getText()
{
    return &oText;
}

Mario::MenuManager* CCFG::getMM()
{
    return &oMM;
}

Mario::Music::Manager* CCFG::getMusic()
{
    return &oMusic;
}

CIMG* CCFG::getSMBLOGO()
{
    return &tSMBLOGO;
}

std::string CCFG::getKeyString(int keyID)
{
    if (keyID >= 97 && keyID <= 122)
    {
        return std::string(1, '0' + (keyID - 32) - 48);
    }

    if (keyID >= 48 && keyID <= 57)
    {
        return std::string(1, '0' + (keyID - 32) - 48);
    }

    switch (keyID)
    {
        case SDLK_ESCAPE:
            return "ESCAPE";
        case SDLK_SPACE:
            return "SPACE";
        case SDLK_LSHIFT:
            return "LSHIFT";
        case SDLK_RSHIFT:
            return "RSHIFT";
        case SDLK_UP:
            return "UP";
        case SDLK_DOWN:
            return "DOWN";
        case SDLK_RIGHT:
            return "RIGHT";
        case SDLK_LEFT:
            return "LEFT";
        case SDLK_LCTRL:
            return "LCTRL";
        case SDLK_RCTRL:
            return "RCTRL";
        default:
            return "NONE";
    }

    return "NONE";
}

} // namespace Mario

Mario::CCFG& getCFG()
{
    static Mario::CCFG cfg;
    return cfg;
}
