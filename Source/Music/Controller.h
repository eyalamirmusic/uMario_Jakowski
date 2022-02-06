#pragma once

namespace Mario::Music::Controller
{
void open();
void setVolume(int volume);
void stop();
bool isPaused();
void resume();
void pause();
}