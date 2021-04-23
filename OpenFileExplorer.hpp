#pragma once
#include "DxLib.h"
#include "picojson.h"
class OpenFileExplorer {
private:
	char fullPath[MAX_PATH], fileName[MAX_PATH];
	OPENFILENAME ofn;

public:
	// �R���X�g���N�^
	OpenFileExplorer();
	
	//���y�t�@�C�����J���ăn���h����Ԃ�
	int OpenAudioFile();
	
	//�摜�t�@�C�����J���ăn���h����Ԃ�
	int OpenImageFile();

	//Json�t�@�C�����J��
	int OpenJsonFile(picojson::value& v);
};