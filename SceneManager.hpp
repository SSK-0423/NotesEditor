#pragma once
#include "ISceneChanger.hpp"
#include "BaseScene.hpp"

class SceneManager : public ISceneChanger, Task {
private:
	BaseScene* mScene;	//�V�[���Ǘ��ϐ�
	eScene mNextScene; // ���̃V�[���Ǘ��ϐ�

public:
	SceneManager();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

	// ISceneChanger�C���^�[�t�F�C�X
	// ���� nextScene �ɃV�[����ύX����
	void ChangeScene(eScene NextScene) override;
};