#pragma once
#include "ISceneChanger.hpp"
#include "BaseScene.hpp"
#include "InputDeviceContainer.hpp"

namespace Game {

	namespace System {

		class SceneManager : public ISceneChanger{
		private:
			//�V�[���Ǘ��ϐ�
			BaseScene* nowScene;	
			// ���̃V�[���Ǘ��ϐ�
			SCENE nextScene;		

		public:
			SceneManager();
			void Update();
			void Draw();
			void Input(const Input::InputDeviceContainer& inputDeviceContainer);

			// ISceneChanger�C���^�[�t�F�C�X
			// ���� nextScene �ɃV�[����ύX����
			void ChangeScene(SCENE NextScene) override;
		};
	}
}