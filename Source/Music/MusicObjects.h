#pragma once

#include <memory>
#include <string>

namespace Mario::Music
{
struct TrackInterface
{
    virtual ~TrackInterface() = default;
    virtual void play() = 0;
};

struct Track
{
    explicit Track(const std::string& trackFile);

    void play() const { track->play(); }

    std::shared_ptr<TrackInterface> track;
};

struct EffectInterface
{
    virtual ~EffectInterface() = default;
    virtual void play(int volume) = 0;
};

struct Effect
{
    explicit Effect(const std::string& trackFile);

    void play(int volume) const;

    std::shared_ptr<EffectInterface> pimpl;
};

namespace Controller
{
void open();
void setVolume(int volume);
void stop();
bool isPaused();
void resume();
void pause();
} // namespace Controller
} // namespace Mario::Music