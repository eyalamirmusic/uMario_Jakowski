#include "MusicObjects.h"
#include "SDL_mixer.h"

namespace Mario::Music
{
Mix_Music* loadMusic(std::string fileName)
{
    fileName = "Resources/sounds/" + fileName + ".wav";
    return Mix_LoadMUS(fileName.c_str());
}

Mix_Chunk* loadChunk(std::string fileName)
{
    fileName = "Resources/sounds/" + fileName + ".wav";
    return Mix_LoadWAV(fileName.c_str());
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

void Controller::setVolume(int volume)
{
    Mix_VolumeMusic(volume);
}

void Controller::stop()
{
    Mix_HaltMusic();
}

bool Controller::isPaused()
{
    return Mix_PausedMusic() == 1;
}

void Controller::resume()
{
    Mix_ResumeMusic();
}
void Controller::pause()
{
    Mix_PauseMusic();
}

void Controller::open()
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

struct SDLEffect : EffectInterface
{
    explicit SDLEffect(const std::string& trackNameToUse)
    {
        chunk = loadChunk(trackNameToUse);
    }

    ~SDLEffect() override { Mix_FreeChunk(chunk); }

    void play(int volume) override
    {
        Mix_VolumeChunk(chunk, volume);
        Mix_PlayChannel(-1, chunk, 0);
    }

    Mix_Chunk* chunk = nullptr;
};

Effect::Effect(const std::string& trackFile)
{
    pimpl = std::make_shared<SDLEffect>(trackFile);
}

void Effect::play(int volume) const
{
    pimpl->play(volume);
}
} // namespace Mario::Music
