#include "DxLib.h"
#include "Music.hpp"
#include "OpenFileExplorer.hpp"

Music::Music() : musicHandle(-1), name("No Data"), bpm(120), beat(4), isMusicLoad(false), isPlay(false) {
}

void Music::SetMusic(const int& handle) noexcept {
	musicHandle = handle;//this->Handle = 0;
}

void Music::LoadMusic() noexcept {
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
void Music::PlayMusic() noexcept {
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

void Music::RestartMusic() noexcept {
	isPlay = true;
	if (CheckSoundMem(musicHandle)) {
		StopSoundMem(musicHandle);
	}
	PlaySoundMem(musicHandle, DX_PLAYTYPE_LOOP, true);
}

int Music::GetTotalTime() noexcept
{
	return GetSoundTotalTime(musicHandle);
}

float Music::GetElapsedTime() noexcept
{
	if (musicHandle != -1)
		return (float)GetSoundCurrentTime(musicHandle);
	else
		return 0.0f;
}

std::string Music::GetName() noexcept {
	return name;
}

float Music::GetBPM() noexcept {
	return bpm;
}

int Music::GetBeat() noexcept {
	return beat;
}

bool Music::IsMusicLoad() noexcept {
	return isMusicLoad;
}

bool Music::IsPlay() noexcept {
	return isPlay;
}

void Music::MusicTimeDraw() noexcept {
	DrawFormatString(0, 0, GetColor(0, 255, 0), "���Đ�����(ms)%d", GetSoundTotalTime(musicHandle));
	DrawFormatString(200, 0, GetColor(0, 255, 0), "�o�ߎ���(ms)%d", GetSoundCurrentTime(musicHandle));
}

void Music::ChangeIsMusicLoad() noexcept {
	isMusicLoad = false;
}

Music::~Music()
{
}