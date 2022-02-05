#pragma once

#include "CommonHeader.h"

namespace Mario
{
enum class Animations
{
    eTOP,
    eRIGHT,
    eRIGHTEND,
    eBOT,
    eLEFT,
    eBOTRIGHTEND,
    eENDBOT1,
    eENDBOT2,
    eENDPOINTS,
    eDEATHNOTHING,
    eDEATHTOP,
    eDEATHBOT,
    eNOTHING,
    ePLAYPIPERIGHT,
    ePLAYPIPETOP,
    eLOADINGMENU,
    eGAMEOVER,
    eBOSSEND1,
    eBOSSEND2,
    eBOSSEND3,
    eBOSSEND4,
    eBOTRIGHTBOSS,
    eBOSSTEXT1,
    eBOSSTEXT2,
    eENDGAMEBOSSTEXT1,
    eENDGAMEBOSSTEXT2,
    eMARIOSPRITE1,
    eVINE1,
    eVINE2,
    eVINESPAWN,
};

class Event
{
public:
    Vector<Animations> vOLDDir;
    Vector<int> vOLDLength;

    Vector<Animations> vNEWDir;
    Vector<int> vNEWLength;

    Vector<int> reDrawX;
    Vector<int> reDrawY;

    enum eventType
    {
        eNormal,
        eEnd,
        eBossEnd,
    };

    eventType eventTypeID = eventType::eNormal;

    void normal();
    void end();

    int iSpeed = 0;

    void resetData();

    int newLevelType = false;
    int newMapXPos = false;
    int newPlayerXPos = false;
    int newPlayerYPos = false;
    bool newMoveMap = false;

    unsigned int iTime = 0;
    int iDelay = 0;

    int newCurrentLevel = 0;
    bool inEvent = false;
    bool newUnderWater = false;

    bool endGame = false;

    // ----- Methods

    void draw(SDL_Renderer* rR);

    void animation();
    void newLevel();

    void resetRedraw();

private:
    bool state = true; // true = OLD, false = NEW
    unsigned int stepID = 0;
};

} // namespace Mario
