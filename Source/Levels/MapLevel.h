#pragma once

class MapLevel
{
public:
    explicit MapLevel(int iBlockID);

    void startBlockAnimation();

    int updateYPos();

    int getBlockID();
    void setBlockID(int iBlockID);

    int getYPos();

    int getNumOfUse();
    void setNumOfUse(int iNumOfUse);

    bool getSpawnMushroom();
    void setSpawnMushroom(bool spawnMushroom);
    bool getPowerUP();
    void setPowerUP(bool powerUP);
    bool getSpawnStar();
    void setSpawnStar(bool spawnStar);

private:
    int iBlockID = 0;

    bool spawnMushroom = false;
    bool powerUP = false; // -- true = powerUP, false = 1UP
    bool spawnStar = false;
    int iNumOfUse = false;

    // ----- Animation -----

    bool blockAnimation = false;
    int iYPos = 0;
    bool bYDirection = false; // ----- true TOP, false BOTTOM

    // ----- Animation -----
};