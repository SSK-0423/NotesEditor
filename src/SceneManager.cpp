#include "DxLib.h"
#include "SceneManager.hpp"
#include "EditScene.hpp"

namespace Game {

	namespace System {

		SceneManager::SceneManager() : nextScene(SCENE_NONE) //���̃V�[���Ǘ��ϐ�
		{
			nowScene = (BaseScene*) new NotesEditor::EditScene(this);
		}

		//�X�V
		void SceneManager::Update() {
			//���̃V�[�����Z�b�g����Ă�����
			if (nextScene != SCENE_NONE) 
			{    
				//���݂̃V�[���̏I�����������s
				//nowScene->Finalize();
				delete nowScene;

				//�V�[���ɂ���ď����𕪊�
				switch (nextScene) 
				{       
					//���̉�ʂ��G�f�B�b�g
					case SCENE_EDIT:        
						//�G�f�B�b�g��ʂ̃C���X�^���X����
						nowScene = (BaseScene*) new NotesEditor::EditScene(this); 
						break;
				}
				nextScene = SCENE_NONE;    //���̃V�[�������N���A
				//nowScene->Initialize();    //�V�[����������
			}

			nowScene->Update(); //�V�[���̍X�V
		}

		//�`��
		void SceneManager::Draw() 
		{
			nowScene->Draw(); //�V�[���̕`��
		}

		void SceneManager::Input(const Input::InputDeviceContainer& inputDeviceContainer)
		{
			nowScene->Input(inputDeviceContainer);
		}

		// ���� nextScene �ɃV�[����ύX����
		void SceneManager::ChangeScene(SCENE nextScene)
		{
			//���̃V�[�����Z�b�g����
			this->nextScene = nextScene;    
		}
	}
}