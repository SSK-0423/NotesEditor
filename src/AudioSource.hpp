#pragma once
#include "GameUtility.hpp"

/*
* オーディオリソースのクラス
*/

namespace Engine
{
	namespace Components
	{
		class AudioSource {
		private:
			Audio audioHandle;
			long long playStartTime;

		public:
			AudioSource();
			AudioSource(const char* filePath);
			void PlayLoop();
			void PlayOneShot();
			void Stop();
			void Replay();
			Audio GetAudioHandle();
			void SetAudioHandle(Audio audioHandle);
			long long GetTotalTime() const;
			long long GetElapsedTime() const;
			int LoadAudio(const char* filePath);
			void ChangeVolume(int volume);
			void SetPlayStartTime(long long time);
			bool IsPlaying();
		};
	}
}