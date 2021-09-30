#pragma once
#include "DxLib.h"
#include "picojson.h"
#include "Singleton.hpp"

class OpenFileExplorer {
private:
	char fullPath[MAX_PATH], fileName[MAX_PATH];
	OPENFILENAME ofn;

public:
	OpenFileExplorer();
	
	//���y�t�@�C�����J���ăn���h����Ԃ�
	int OpenAudioFile() noexcept;
	
	//�摜�t�@�C�����J���ăn���h����Ԃ�
	int OpenImageFile() noexcept;

	//Json�t�@�C�����J��
	int OpenJsonFile(picojson::value& v) noexcept;
};