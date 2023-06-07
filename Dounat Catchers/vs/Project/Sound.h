#ifndef SOUND_H
#define SOUND_H

#include <SDL/SDL_mixer.h>


namespace Engine {
	class Sound
	{
	public:
		Sound(const char* path);
		~Sound();
		bool IsPlaying();
		void Play(bool loop);
		void SetVolume(int volume);
		int GetVolume();
	private:
		Mix_Chunk* sound = NULL;
		int volume = 100, minVolume = 10, maxVolume = 100;
	};

}

#endif

