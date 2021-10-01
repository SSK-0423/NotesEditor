#include "AudioSource.hpp"
#include "DxLib.h"

Engine::Components::AudioSource::AudioSource() : audioHandle(-1)
{
}

Engine::Components::AudioSource::AudioSource(const char* filePath) : audioHandle(LoadAudio(filePath))
{
}

int Engine::Components::AudioSource::PlayAudio()
{
	bool isPlaying = CheckSoundMem(audioHandle);
	if (audioHandle == RESULT::RESULT_ERROR || isPlaying)
		return RESULT::RESULT_ERROR;

	// 0:ê¨å˜ -1:é∏îs
	return PlaySoundMem(audioHandle, DX_PLAYTYPE_LOOP, false);
}

int Engine::Components::AudioSource::StopAudio()
{
	// 0:ê¨å˜ -1:é∏îs
	return StopSoundMem(audioHandle);
}

int Engine::Components::AudioSource::ReplayAudio()
{
	bool isPlaying = CheckSoundMem(audioHandle);
	if (isPlaying)
	{
		if (StopAudio() == RESULT::RESULT_ERROR)
			return RESULT::RESULT_ERROR;
	}
	// 0:ê¨å˜ -1:é∏îs
	return PlaySoundMem(audioHandle, DX_PLAYTYPE_LOOP, true);
}

int Engine::Components::AudioSource::LoadAudio(const char* filePath)
{
	audioHandle = LoadSoundMem(filePath);
	if (audioHandle == RESULT::RESULT_ERROR)
		return RESULT::RESULT_ERROR;

	return RESULT::RESULT_SUCCEED;
}