#pragma once

#include <ea_data_structures/ea_data_structures.h>
#include "Track.h"
#include "Effect.h"
#include "MusicConsts.h"

namespace Mario::Music
{
class Manager
{
public:
    Manager();

    void changeMusic(bool musicByLevel, bool forceChange);

    void playTrack();
    void playTrack(Tracks musicID);
    void stopTrack();
    void pauseTrack();

    void playEffect(Effects chunkID);

    int getVolume() const;
    void setVolume(int volumeToUse);

    bool isMusicPlaying() const { return !musicStopped; }

private:
    void addTrack(const std::string& name);
    void addEffect(const std::string& name);

    EA::Vector<Track> tracks;
    EA::Vector<Effect> effects;

    int volume = 0;
    Tracks currentTrack = Tracks::Nothing;
    bool musicStopped = false;
};
} // namespace Mario::Music