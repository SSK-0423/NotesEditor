#pragma once
#include "GameSymbol.hpp"

namespace Engine
{
	namespace Components
	{
		class AudioSource {
		private:
			Audio audioHandle;
		public:
			AudioSource();
			AudioSource(const char* filePath);
			int PlayAudioLoop();
			int PlayOneShot();
			int StopAudio();
			int ReplayAudio();
			int GetTotalTime() const;
			float GetElapsedTime() const;
			int LoadAudio(const char* filePath);
			int ChangeVolume(int volume);
		};
	}
}