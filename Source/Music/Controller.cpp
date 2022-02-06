#include "Controller.h"
#include "SDL_mixer.h"

namespace Mario::Music
{
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
} // namespace Mario::Music