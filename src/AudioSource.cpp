#include "AudioSource.hpp"
#include "DxLib.h"

Engine::Components::AudioSource::AudioSource() : audioHandle(-1), playStartTime(0LL)
{
}

Engine::Components::AudioSource::AudioSource(const char* filePath) : audioHandle(LoadSoundMem(filePath)), playStartTime(0LL)
{
}

void Engine::Components::AudioSource::PlayLoop()
{
	SetSoundCurrentTime(playStartTime, audioHandle);
	PlaySoundMem(audioHandle, DX_PLAYTYPE_LOOP, false);
}

void Engine::Components::AudioSource::PlayOneShot()
{
	PlaySoundMem(audioHandle, DX_PLAYTYPE_BACK, true);
}

void Engine::Components::AudioSource::Stop()
{
	StopSoundMem(audioHandle);
}

void Engine::Components::AudioSource::Replay()
{
	// 同じ音源が複数同時に再生されるのを防ぐために
	// 既に再生中の場合は一旦再生を止める
	if (IsPlaying()) Stop();
	PlaySoundMem(audioHandle, DX_PLAYTYPE_LOOP, true);
}

Audio Engine::Components::AudioSource::GetAudioHandle()
{
	return audioHandle;
}

void Engine::Components::AudioSource::SetAudioHandle(Audio audioHandle)
{
	this->audioHandle = audioHandle;
}

long long Engine::Components::AudioSource::GetTotalTime() const
{
	return GetSoundTotalTime(audioHandle);
}

long long Engine::Components::AudioSource::GetElapsedTime() const
{
	return GetSoundCurrentTime(audioHandle);
}

int Engine::Components::AudioSource::LoadAudio(const char* filePath)
{
	audioHandle = LoadSoundMem(filePath);
	if (audioHandle == NONE)
		return RESULT::RESULT_ERROR;
	return RESULT::RESULT_SUCCEED;
}

void Engine::Components::AudioSource::ChangeVolume(int volume)
{
	ChangeVolumeSoundMem(volume, audioHandle);
}

void Engine::Components::AudioSource::SetPlayStartTime(long long time)
{
	playStartTime = time;
}

bool Engine::Components::AudioSource::IsPlaying()
{
	// ハンドルが設定されていない時、
	// CheckSoundMemはtrueを返してしまうので、
	// ハンドルが設定されてない場合はfalseを返すようにする
	if (audioHandle == NONE) return false;
	return CheckSoundMem(audioHandle);
}
