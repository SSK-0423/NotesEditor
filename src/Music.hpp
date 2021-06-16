#pragma once
#include <string>
#include "picojson.h"
class Music {
private:
	std::string str;
	//json�t�@�C��
	picojson::value json;

	int musicHandle;
	//�Ȗ�
	std::string name;
	//BPM
	float bpm;
	//���q
	int beat;

	//�Ȃ��ǂݍ��܂ꂽ���ǂ���
	bool isMusicLoad;
	//�Ȃ��Đ������ǂ���
	bool isPlay;

public:
	//�R���X�g���N�^
	Music();
	//�Ȃ̃Z�b�g
	void SetMusic(const int& handle) noexcept;
	//�Ȃ̓Ǎ�
	void LoadMusic() noexcept;
	//�f�X�g���N�^
	virtual ~Music() noexcept;
	//�Ȃ̍Đ��E��~
	void PlayMusic() noexcept;
	//�Ȃ��ŏ�����Đ�
	void RestartMusic() noexcept;
	//�Ȃ̒������擾
	int GetTotalTime() noexcept;
	//���݂̍Đ��ʒu���擾
	float GetElapsedTime() noexcept;
	//�Ȗ��擾
	std::string GetName() noexcept;
	//BPM�擾
	float GetBPM() noexcept;
	//���q�擾
	int GetBeat() noexcept;
	//�Ȃ��ǂݍ��܂ꂽ���ǂ������擾
	bool IsMusicLoad() noexcept;
	//�Ȃ��Đ������ǂ���
	bool IsPlay() noexcept;
	//�t���O�ύX
	void ChangeIsMusicLoad() noexcept;
	void MusicTimeDraw() noexcept;
};