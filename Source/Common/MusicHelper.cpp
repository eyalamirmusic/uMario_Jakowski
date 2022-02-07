#include "MusicHelper.h"

#include "Music/Music.h"
#include "Core.h"

namespace Mario::Music::Helpers
{
void changeMusic()
{
    auto* music = getCFG().getMusic();

    auto newTrack = music->getCurrentTrack();

    auto* map = CCore::getMap();

    if (map->getInEvent() && map->getEvent()->inEvent)
    {
        newTrack = Tracks::Nothing;
        music->playEffect(Effects::Intermission);
    }
    else
    {
        newTrack = getTrack(map->getMapTime(), map->getLevelType());

        if (map->getLevelType() == 100)
        {
            music->playEffect(Effects::Intermission);
            map->setLevelType(0);
        }
    }

    music->replaceTrack(newTrack);
}
} // namespace Mario::Music::Helpers