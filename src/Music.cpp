#include "DxLib.h"
#include "Music.hpp"
#include "OpenFileExplorer.hpp"

Engine::Components::Music::Music() : musicHandle(-1), name("No Data"), bpm(120), beat(4), isMusicLoad(false), isPlay(false) {
}

void Engine::Components::Music::SetMusic(const int& handle){
	musicHandle = handle;//this->Handle = 0;
}

void Engine::Components::Music::LoadMusic(){
	OpenFileExplorer open;
	//json�t�@�C����ǂݍ���
	if (open.OpenJsonFile(json) != -1) {
		//���ɓǂݍ��񂾋Ȃ��폜
		InitSoundMem();
		//�Ȗ��Ǎ�
		name = json.get<picojson::object>()["NAME"].get<std::string>();
		//BPM�ǂݍ���
		bpm = json.get<picojson::object>()["BPM"].get<double>();
		//���q�ǂݍ���
		beat = json.get<picojson::object>()["BEAT"].get<double>();
		//�t�@�C���p�X�Ǎ�
		std::string path = json.get<picojson::object>()["PATH"].get<std::string>();
		//�ȓǂݍ���
		musicHandle = LoadSoundMem(path.c_str());
		if (musicHandle != -1) {
			isMusicLoad = true;
		}
	}
}

// �Ȃ̍Đ��E��~
void Engine::Components::Music::PlayMusic(){
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "Music�N���X�̊֐�");
	if (!CheckSoundMem(musicHandle)) {
		PlaySoundMem(musicHandle, DX_PLAYTYPE_LOOP, false);
		isPlay = true;
	}
	else {
		StopSoundMem(musicHandle);
		isPlay = false;
	}
	//isPlay = true;
}

void Engine::Components::Music::RestartMusic(){
	isPlay = true;
	if (CheckSoundMem(musicHandle)) {
		StopSoundMem(musicHandle);
	}
	PlaySoundMem(musicHandle, DX_PLAYTYPE_LOOP, true);
}

int Engine::Components::Music::GetTotalTime()
{
	return GetSoundTotalTime(musicHandle);
}

float Engine::Components::Music::GetElapsedTime()
{
	if (musicHandle != -1)
		return (float)GetSoundCurrentTime(musicHandle);
	else
		return 0.0f;
}

std::string Engine::Components::Music::GetName(){
	return name;
}

float Engine::Components::Music::GetBPM(){
	return bpm;
}

int Engine::Components::Music::GetBeat(){
	return beat;
}

bool Engine::Components::Music::IsMusicLoad() {
	return isMusicLoad;
}

bool Engine::Components::Music::IsPlay(){
	return isPlay;
}

void Engine::Components::Music::MusicTimeDraw(){
	DrawFormatString(0, 0, GetColor(0, 255, 0), "���Đ�����(ms)%d", GetSoundTotalTime(musicHandle));
	DrawFormatString(200, 0, GetColor(0, 255, 0), "�o�ߎ���(ms)%d", GetSoundCurrentTime(musicHandle));
}

void Engine::Components::Music::ChangeIsMusicLoad(){
	isMusicLoad = false;
}

Engine::Components::Music::~Music()
{
}