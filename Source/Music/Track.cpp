#include "Track.h"
#include "SDL_mixer.h"

namespace Mario::Music
{
Mix_Music* loadMusic(std::string fileName)
{
    fileName = "Resources/sounds/" + fileName + ".wav";
    return Mix_LoadMUS(fileName.c_str());
}

struct SDLTrack : TrackInterface
{
    explicit SDLTrack(const std::string& trackNameToUse)
    {
        music = loadMusic(trackNameToUse);
    }

    ~SDLTrack() override { Mix_FreeMusic(music); }

    void play() override { Mix_PlayMusic(music, -1); }

    Mix_Music* music = nullptr;
};

Track::Track(const std::string& trackFile)
{
    track = std::make_shared<SDLTrack>(trackFile);
}
} // namespace Mario::Music