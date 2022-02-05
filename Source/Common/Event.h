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
    void resetData();

    void draw(SDL_Renderer* rR);
    void animation();
    void newLevel() const;
    void resetRedraw();

    Vector<Animations> vOLDDir;
    Vector<int> vOLDLength;

    Vector<Animations> vNEWDir;
    Vector<int> vNEWLength;

    Vector<Point<int>> redraw;

    enum eventType
    {
        eNormal,
        eEnd,
        eBossEnd,
    };

    eventType eventTypeID = eventType::eNormal;


    int iSpeed = 0;

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


private:
    void normal();
    void end();

    bool state = true; // true = OLD, false = NEW
    unsigned int stepID = 0;
};

} // namespace Mario
