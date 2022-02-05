#pragma once

#include "Graphics/Text.h"
#include "Menus/MenuManager.h"
#include "Music/Music.h"

class CCFG
{
public:
    ~CCFG();

    static int GAME_WIDTH, GAME_HEIGHT;
    static bool keySpace;
    static int keyIDA, keyIDS, keyIDD, keyIDSpace, keyIDShift;

    static std::string getKeyString(int keyID);

    static CIMG* getSMBLOGO();

    static Text* getText();

    static Mario::MenuManager* getMM();
    static Mario::Music::Manager* getMusic();

    static bool canMoveBackward;

private:
    static Mario::MenuManager* oMM;
    static Text* oText;
    static CIMG* tSMBLOGO;
    static Mario::Music::Manager* oMusic;

};
