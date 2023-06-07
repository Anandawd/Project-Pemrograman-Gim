#ifndef MUSIC_H
#define MUSIC_H

#include <SDL/SDL_mixer.h>


namespace Engine {
	class Music
	{
	public:
		Music(const char* path);
		~Music();
		bool IsPaused();
		bool IsPlaying();
		void Play(bool loop);
		void Pause();
		void Resume();
		void Stop();
		void SetVolume(int volume);
		int GetVolume();
	private:
		Mix_Music* music = NULL;
		int volume = 100, minVolume = 10, maxVolume = 100;
	};
}

#endif

