#pragma once

typedef enum {
	eScene_Menu,
	eScene_Game,
	eScene_Config,

	eScene_None,
} eScene;

//�V�[����ύX���邽�߂̃C���^�[�t�F�C�X�N���X
class ISceneChanger {
public:
	virtual ~ISceneChanger() = 0;
	virtual void ChangeScene(eScene NextScene) = 0;//�w��V�[���ɕύX����
};