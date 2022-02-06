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
}