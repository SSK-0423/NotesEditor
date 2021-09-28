#include "SceneManager.hpp"
#include "EditScene.hpp"

SceneManager::SceneManager() : nextScene(SCENE_NONE)
{
	nowScene = (BaseScene*) new NotesEditor::EditScene(this);
}

void SceneManager::Update()
{
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
		//nowScene->Initialize();  //�V�[����������
	}

	nowScene->Update(); //�V�[���̍X�V
}

void SceneManager::Draw()
{
	nowScene->Draw();
}

void SceneManager::ChangeScene(SCENE NextScene)
{
	this->nextScene = nextScene;
}
