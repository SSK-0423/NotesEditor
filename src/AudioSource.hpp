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
			int PlayAudio();
			int StopAudio();
			int ReplayAudio();
			int LoadAudio(const char* filePath);
		};
	}
}