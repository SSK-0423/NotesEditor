#include "DxLib.h"
#include "SceneManager.hpp"
#include "Editor.hpp"

SceneManager::SceneManager() :
	mNextScene(eScene_None) //���̃V�[���Ǘ��ϐ�
{
	mScene = (BaseScene*) new Editor(this);
	mScene->Initialize();
}

//������
void SceneManager::Initialize() {
	mScene->Initialize();
}

//�I������
void SceneManager::Finalize() {
	mScene->Finalize();
}

//�X�V
void SceneManager::Update() {
	if (mNextScene != eScene_None) {    //���̃V�[�����Z�b�g����Ă�����
		mScene->Finalize();//���݂̃V�[���̏I�����������s
		delete mScene;
		switch (mNextScene) {       //�V�[���ɂ���ď����𕪊�
		case eScene_Edit:        //���̉�ʂ����j���[�Ȃ�
			mScene = (BaseScene*) new Editor(this); //���j���[��ʂ̃C���X�^���X�𐶐�����
			break;//�ȉ���
		}
		mNextScene = eScene_None;    //���̃V�[�������N���A
		mScene->Initialize();    //�V�[����������
	}

	mScene->Update(); //�V�[���̍X�V
}

//�`��
void SceneManager::Draw() {
	mScene->Draw(); //�V�[���̕`��
}

// ���� nextScene �ɃV�[����ύX����
void SceneManager::ChangeScene(eScene NextScene) {
	mNextScene = NextScene;    //���̃V�[�����Z�b�g����
}