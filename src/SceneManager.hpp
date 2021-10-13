#pragma once
#include "ISceneChanger.hpp"
#include "BaseScene.hpp"

/*
	�e�V�[���̎��s�ƃV�[���J�ڂ�S���N���X
*/
namespace Engine
{
	namespace Scene {

		class SceneManager : public ISceneChanger {
		private:
			//�V�[���Ǘ��ϐ�
			BaseScene* nowScene;
			// ���̃V�[���Ǘ��ϐ�
			SCENE nextScene;

		public:
			SceneManager();
			void Update();
			void Draw();

			// ISceneChanger�C���^�[�t�F�C�X
			// ���� nextScene �ɃV�[����ύX����
			void ChangeScene(SCENE NextScene) override;
		};
	}
}
