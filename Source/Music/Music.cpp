#include "Music.h"
#include "Common/Core.h"
#include "SDL_mixer.h"

namespace Mario::Music
{
Manager::Manager()
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    tracks.push_back(loadMusic("overworld"));
    tracks.push_back(loadMusic("overworld-fast"));
    tracks.push_back(loadMusic("underground"));
    tracks.push_back(loadMusic("underground-fast"));
    tracks.push_back(loadMusic("underwater"));
    tracks.push_back(loadMusic("underwater-fast"));
    tracks.push_back(loadMusic("castle"));
    tracks.push_back(loadMusic("castle-fast"));
    tracks.push_back(loadMusic("lowtime"));
    tracks.push_back(loadMusic("starmusic"));
    tracks.push_back(loadMusic("starmusic-fast"));
    tracks.push_back(loadMusic("scorering"));

    effects.push_back(loadChunk("coin"));
    effects.push_back(loadChunk("blockbreak"));
    effects.push_back(loadChunk("blockhit"));
    effects.push_back(loadChunk("boom"));
    effects.push_back(loadChunk("bowserfall"));
    effects.push_back(loadChunk("bridgebreak"));
    effects.push_back(loadChunk("bulletbill"));
    effects.push_back(loadChunk("death"));
    effects.push_back(loadChunk("fire"));
    effects.push_back(loadChunk("fireball"));
    effects.push_back(loadChunk("gameover"));
    effects.push_back(loadChunk("intermission"));
    effects.push_back(loadChunk("jump"));
    effects.push_back(loadChunk("jumpbig"));
    effects.push_back(loadChunk("levelend"));
    effects.push_back(loadChunk("lowtime"));
    effects.push_back(loadChunk("mushroomappear"));
    effects.push_back(loadChunk("mushroomeat"));
    effects.push_back(loadChunk("oneup"));
    effects.push_back(loadChunk("pause"));
    effects.push_back(loadChunk("shrink"));
    effects.push_back(loadChunk("rainboom"));
    effects.push_back(loadChunk("shot"));
    effects.push_back(loadChunk("shrink"));
    effects.push_back(loadChunk("stomp"));
    effects.push_back(loadChunk("swim"));
    effects.push_back(loadChunk("vine"));
    effects.push_back(loadChunk("castleend"));
    effects.push_back(loadChunk("princessmusic"));

    setVolume(100);
    currentMusic = Tracks::mNOTHING;
}

Manager::~Manager()
{
    for (auto& i: tracks)
        Mix_FreeMusic(i);

    tracks.clear();

    for (auto& i: effects)
        Mix_FreeChunk(i);

    effects.clear();
}

void Manager::changeMusic(bool musicByLevel, bool forceChange)
{
    Tracks eNew = currentMusic;

    if (musicByLevel)
    {
        if (CCore::getMap()->getInEvent() && CCore::getMap()->getEvent()->inEvent)
        {
            eNew = Tracks::mNOTHING;
            PlayChunk(Effects::cINTERMISSION);
        }
        else
        {
            switch (CCore::getMap()->getLevelType())
            {
                case 0:
                case 4:
                    eNew = CCore::getMap()->getMapTime() > 90
                               ? Tracks::mOVERWORLD
                               : Tracks::mOVERWORLDFAST;
                    break;
                case 1:
                    eNew = CCore::getMap()->getMapTime() > 90
                               ? Tracks::mUNDERWORLD
                               : Tracks::mUNDERWORLDFAST;
                    break;
                case 2:
                    eNew = CCore::getMap()->getMapTime() > 90
                               ? Tracks::mUNDERWATER
                               : Tracks::mUNDERWATERFAST;
                    break;
                case 3:
                    eNew = CCore::getMap()->getMapTime() > 90 ? Tracks::mCASTLE
                                                              : Tracks::mCASTLEFAST;
                    break;
                case 100:
                    eNew = Tracks::mNOTHING;
                    PlayChunk(Effects::cINTERMISSION);
                    CCore::getMap()->setLevelType(0);
                    break;
                default:
                    eNew = Tracks::mNOTHING;
                    break;
            }
        }
    }

    if (currentMusic != eNew || forceChange)
    {
        StopMusic();
        currentMusic = eNew;
        PlayMusic();
    }
}

void Manager::PlayMusic()
{
    if (currentMusic != Tracks::mNOTHING)
    {
        Mix_PlayMusic(tracks[(int) currentMusic - 1], -1);
        musicStopped = false;
    }
    else
    {
        StopMusic();
    }
}

void Manager::PlayMusic(Tracks musicID)
{
    if (musicID != Tracks::mNOTHING)
    {
        Mix_PlayMusic(tracks[(int) musicID - 1], -1);
        musicStopped = false;
        currentMusic = musicID;
    }
    else
    {
        StopMusic();
        currentMusic = Tracks::mNOTHING;
    }
}

void Manager::StopMusic()
{
    if (!musicStopped)
    {
        Mix_HaltMusic();
        musicStopped = true;
    }
}

void Manager::PauseMusic()
{
    if (Mix_PausedMusic() == 1)
    {
        Mix_ResumeMusic();
        musicStopped = false;
    }
    else
    {
        Mix_PauseMusic();
        musicStopped = true;
    }
}

void Manager::PlayChunk(Effects chunkID)
{
    auto id = (int) chunkID;
    Mix_VolumeChunk(effects[id], volume);
    Mix_PlayChannel(-1, effects[id], 0);
}

Mix_Music* Manager::loadMusic(std::string fileName)
{
    fileName = "files/sounds/" + fileName + ".wav";
    return Mix_LoadMUS(fileName.c_str());
}

Mix_Chunk* Manager::loadChunk(std::string fileName)
{
    fileName = "files/sounds/" + fileName + ".wav";
    return Mix_LoadWAV(fileName.c_str());
}

int Manager::getVolume() const
{
    return volume;
}

void Manager::setVolume(int volumeToUse)
{
    volume = volumeToUse;
    Mix_VolumeMusic(volumeToUse);
}

} // namespace Mario::Music
