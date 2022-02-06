#pragma once

#include "CommonHeader.h"
#include "SDL_mixer.h"
#include "MusicObjects.h"

namespace Mario::Music
{
enum class Tracks
{
    Nothing,
    Overworld,
    OverworldFast,
    Underworld,
    UnderworldFast,
    Underwater,
    UnderwaterFast,
    Castle,
    CastleFast,
    LowTime,
    Star,
    StarFast,
    Scorering,
};

enum class Effects
{
    Coin,
    BlockBreak,
    BlockHit,
    Boom,
    BowserFall,
    BridgeBreak,
    BulletBill,
    Death,
    Fire,
    Fireball,
    GameOver,
    Intermission,
    Jump,
    JumpBig,
    LevelEnd,
    LowTime,
    MushroomMapper,
    MushroomMeat,
    OneUp,
    Pause,
    Pipe,
    RainBoom,
    Shot,
    Shrink,
    Stomp,
    Swim,
    Vine,
    CastleEnd,
    PrincessMusic,
};

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

    Vector<Track> tracks;
    Vector<Effect> effects;

    int volume = 0;
    Tracks currentTrack = Tracks::Nothing;
    bool musicStopped = false;
};
} // namespace Mario::Music