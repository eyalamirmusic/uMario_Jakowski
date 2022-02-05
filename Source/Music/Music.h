#pragma once

#include "CommonHeader.h"
#include "SDL_mixer.h"

namespace Mario::Music
{
enum class Tracks
{
    mNOTHING,
    mOVERWORLD,
    mOVERWORLDFAST,
    mUNDERWORLD,
    mUNDERWORLDFAST,
    mUNDERWATER,
    mUNDERWATERFAST,
    mCASTLE,
    mCASTLEFAST,
    mLOWTIME,
    mSTAR,
    mSTARFAST,
    mSCORERING,
};

enum class Effects
{
    cCOIN,
    cBLOCKBREAK,
    cBLOCKHIT,
    cBOOM,
    cBOWSERFALL,
    cBRIDGEBREAK,
    cBULLETBILL,
    cDEATH,
    cFIRE,
    cFIREBALL,
    cGAMEOVER,
    cINTERMISSION,
    cJUMP,
    cJUMPBIG,
    cLEVELEND,
    cLOWTIME,
    cMUSHROOMAPPER,
    cMUSHROOMMEAT,
    cONEUP,
    cPASUE,
    cPIPE,
    cRAINBOOM,
    cSHOT,
    cSHRINK,
    cSTOMP,
    cSWIM,
    cVINE,
    cCASTLEEND,
    cPRINCESSMUSIC,
};

class Manager
{
public:
    Manager();
    ~Manager();

    void changeMusic(bool musicByLevel, bool forceChange);

    void PlayMusic();
    void PlayMusic(Tracks musicID);
    void StopMusic();
    void PauseMusic();

    void PlayChunk(Effects chunkID);

    Mix_Music* loadMusic(std::string fileName);
    Mix_Chunk* loadChunk(std::string fileName);

    int getVolume() const;
    void setVolume(int volumeToUse);

    bool isMusicPlaying() const { return !musicStopped; }

private:
    std::vector<Mix_Music*> tracks;
    std::vector<Mix_Chunk*> effects;

    int volume = 0;
    Tracks currentMusic = Tracks::mNOTHING;
    bool musicStopped = false;
};
} // namespace Mario::Music