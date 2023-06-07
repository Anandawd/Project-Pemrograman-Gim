#include "Sound.h"

Engine::Sound::Sound(const char* path)
{
	sound = Mix_LoadWAV(path);
}

Engine::Sound::~Sound()
{
	Mix_FreeChunk(sound);
}

bool Engine::Sound::IsPlaying()
{
	return Mix_Playing(-1) == 1;
}

void Engine::Sound::Play(bool loop)
{
	Mix_PlayChannel(-1, sound, loop ? -1 : 0);
}

void Engine::Sound::SetVolume(int volume)
{
	if (volume > maxVolume) {
		volume = maxVolume;
	}
	else if (volume < minVolume) {
		volume = minVolume;
	}

	this->volume = volume;
	Mix_VolumeChunk(sound, volume * 128 / maxVolume);
}

int Engine::Sound::GetVolume() {
	return volume;
}
