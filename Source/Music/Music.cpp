#include "Music.h"
#include "Controller.h"

namespace Mario::Music
{
Tracks getTrack(int time, int levelType)
{
    switch (levelType)
    {
        case 0:
        case 4:
            return time > 90 ? Tracks::Overworld : Tracks::OverworldFast;
        case 1:
            return time > 90 ? Tracks::Underworld : Tracks::UnderworldFast;
        case 2:
            return time > 90 ? Tracks::Underwater : Tracks::UnderwaterFast;
        case 3:
            return time > 90 ? Tracks::Castle : Tracks::CastleFast;
        default:
            return Tracks::Nothing;
    }
}

Manager::Manager()
{
    Controller::open();

    addTrack("overworld");
    addTrack("overworld-fast");
    addTrack("underground");
    addTrack("underground-fast");
    addTrack("underwater");
    addTrack("underwater-fast");
    addTrack("castle");
    addTrack("castle-fast");
    addTrack("lowtime");
    addTrack("starmusic");
    addTrack("starmusic-fast");
    addTrack("scorering");

    addEffect("coin");
    addEffect("blockbreak");
    addEffect("blockhit");
    addEffect("boom");
    addEffect("bowserfall");
    addEffect("bridgebreak");
    addEffect("bulletbill");
    addEffect("death");
    addEffect("fire");
    addEffect("fireball");
    addEffect("gameover");
    addEffect("intermission");
    addEffect("jump");
    addEffect("jumpbig");
    addEffect("levelend");
    addEffect("lowtime");
    addEffect("mushroomappear");
    addEffect("mushroomeat");
    addEffect("oneup");
    addEffect("pause");
    addEffect("shrink");
    addEffect("rainboom");
    addEffect("shot");
    addEffect("shrink");
    addEffect("stomp");
    addEffect("swim");
    addEffect("vine");
    addEffect("castleend");
    addEffect("princessmusic");

    setVolume(100);
    currentTrack = Tracks::Nothing;
}

void Manager::addTrack(const std::string& name)
{
    tracks.create(name);
}

void Manager::addEffect(const std::string& name)
{
    effects.create(name);
}

void Manager::playTrack()
{
    if (currentTrack != Tracks::Nothing)
    {
        tracks[(int) currentTrack - 1].play();
        musicStopped = false;
    }
    else
    {
        stopTrack();
    }
}

void Manager::playTrack(Tracks musicID)
{
    if (musicID != Tracks::Nothing)
    {
        tracks[(int) musicID - 1].play();
        musicStopped = false;
        currentTrack = musicID;
    }
    else
    {
        stopTrack();
        currentTrack = Tracks::Nothing;
    }
}

void Manager::stopTrack()
{
    if (!musicStopped)
    {
        Controller::stop();
        musicStopped = true;
    }
}

void Manager::pauseTrack()
{
    if (Controller::isPaused())
    {
        Controller::resume();
        musicStopped = false;
    }
    else
    {
        Controller::pause();
        musicStopped = true;
    }
}

void Manager::playEffect(Effects chunkID)
{
    auto id = (int) chunkID;
    effects[id].play(volume);
}

int Manager::getVolume() const
{
    return volume;
}

void Manager::setVolume(int volumeToUse)
{
    volume = volumeToUse;
    Controller::setVolume(volume);
}

void Manager::replaceTrack(Tracks track)
{
    stopTrack();
    currentTrack = track;
    playTrack();
}
} // namespace Mario::Music
