#pragma once

#include "Graphics/Text.h"
#include "Menus/MenuManager.h"
#include "Music/Music.h"

namespace Mario
{
class CCFG
{
public:
    static std::string getKeyString(int keyID);

    CIMG* getSMBLOGO();

    Text* getText();

    MenuManager* getMM();
    Music::Manager* getMusic();

    int GAME_WIDTH = 800;
    int GAME_HEIGHT = 448;
    bool keySpace = false;
    int keyIDA = 0;
    int keyIDS = 0;
    int keyIDD = 0;
    int keyIDSpace = 0;
    int keyIDShift = 0;

    bool canMoveBackward = true;

private:
    MenuManager oMM;
    Text oText;
    CIMG tSMBLOGO;
    Music::Manager oMusic;
};

} // namespace Mario

Mario::CCFG& getCFG();
