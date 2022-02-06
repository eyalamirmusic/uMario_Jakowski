#include "Effect.h"
#include "SDL_mixer.h"

namespace Mario::Music
{
Mix_Chunk* loadChunk(std::string fileName)
{
    fileName = "Resources/sounds/" + fileName + ".wav";
    return Mix_LoadWAV(fileName.c_str());
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