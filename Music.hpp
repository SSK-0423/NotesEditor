#pragma once
#include <string>
#include "picojson.h"
class Music {
private:
	std::string str;
	//json�t�@�C��
	picojson::value json;

public:
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
	//�R���X�g���N�^
	Music();
	//�Ȃ̃Z�b�g
	void SetMusic(const int& handle);
	//�Ȃ̓Ǎ�
	void LoadMusic();
	//�f�X�g���N�^
	virtual ~Music();
	//�Ȃ̍Đ��E��~
	void PlayMusic();
	//�Ȃ��ŏ�����Đ�
	void RestartMusic();
	//�Ȃ̒������擾
	int GetTotalTime();
	//���݂̍Đ��ʒu���擾
	float GetElapsedTime();

	void MusicTimeDraw();
};