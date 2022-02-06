#pragma once

#include <memory>
#include <string>

namespace Mario::Music
{
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
} // namespace Mario::Music