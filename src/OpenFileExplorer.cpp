#include "OpenFileExplorer.hpp"
#include "DxLib.h"
#include <string.h>
#include <fstream>
#include <cstring>
#include <Windows.h>
//OPENFILENAME�\���̂̏�����
OpenFileExplorer::OpenFileExplorer(){

	memset(&ofn, 0, sizeof(OPENFILENAME));
	memset(fullPath, 0, sizeof(fullPath));
	memset(fileName, 0, sizeof(fileName));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GetMainWindowHandle();//���C���E�B���h�E�̃n���h�����擾

	//�t�@�C�����̃t�B���^�ݒ�
	ofn.lpstrFilter = "�S�Ẵt�@�C��(*.*)\0*.*\0";
	ofn.lpstrFile = fullPath;
	//�t�@�C���̃t���p�X��ۑ�����o�b�t�@�T�C�Y�w��
	ofn.nMaxFile = sizeof(fullPath);

	ofn.lpstrFileTitle = fileName;
	ofn.nMaxFileTitle = sizeof(fileName);

	// �_�C�A���O�{�b�N�X�̓�����w��
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	// ���[�U�[���g���q����͂��Ȃ������ꍇ�̃f�t�H���g�g���q
	ofn.lpstrDefExt = "";
	
	ofn.lpstrInitialDir = "C:\\DxLib\\MyProjects\\NotesEditor";

	// �_�C�A���O�{�b�N�X�̃^�C�g��
	ofn.lpstrTitle = "�t�@�C���̓ǂݍ���";
}

int OpenFileExplorer::OpenAudioFile() {
	ofn.lpstrTitle = "���y�t�@�C���̓ǂݍ���";
	ofn.lpstrFilter = "WAV�t�@�C��(*.wav)\0*.wav\0MP3�t�@�C��(*.mp3)\0*.mp3\0\0";
	if (GetOpenFileName(&ofn) != 0) {
		return LoadSoundMem(fullPath);
	}
	return -1;
}

int OpenFileExplorer::OpenImageFile() {
	ofn.lpstrTitle = "�摜�t�@�C���̓ǂݍ���";
	ofn.lpstrFilter = "PNG�t�@�C��(*.png)\0*.png\0JPEG�t�@�C��(*.jpg)\0*.jpg\0\0";
	if (GetOpenFileName(&ofn) != 0) {
		return LoadGraph(fullPath);
	}
	return -1;
}

int OpenFileExplorer::OpenJsonFile(picojson::value& v) {
	ofn.lpstrTitle = "Json�t�@�C���̓ǂݍ���";
	ofn.lpstrFilter = "Json�t�@�C��(*.json)\0*.json\0\0";
	if (GetOpenFileName(&ofn) != 0) {
		std::ifstream ifs;
		ifs.open(fullPath);
		ifs >> v;
		ifs.close();
		//�J�����g�f�B���N�g����߂�
		SetCurrentDirectory("..");
		return 0;
	}
	return -1;
}