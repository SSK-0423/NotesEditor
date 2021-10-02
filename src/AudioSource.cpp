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
	if (audioHandle == NONE || isPlaying)
		return RESULT::RESULT_ERROR;

	// 0:���� -1:���s
	return PlaySoundMem(audioHandle, DX_PLAYTYPE_LOOP, false);
}

int Engine::Components::AudioSource::StopAudio()
{
	// 0:���� -1:���s
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
	// 0:���� -1:���s
	return PlaySoundMem(audioHandle, DX_PLAYTYPE_LOOP, true);
}

int Engine::Components::AudioSource::GetTotalTime()
{
	return GetSoundTotalTime(audioHandle);
}

float Engine::Components::AudioSource::GetElapsedTime()
{
	if (audioHandle == NONE)
		return RESULT::RESULT_ERROR;
	
	return static_cast<float>(GetSoundCurrentTime(audioHandle));
}

int Engine::Components::AudioSource::LoadAudio(const char* filePath)
{
	audioHandle = LoadSoundMem(filePath);
	if (audioHandle == NONE)
		return RESULT::RESULT_ERROR;

	return RESULT::RESULT_SUCCEED;
}