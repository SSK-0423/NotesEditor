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
			BaseScene* nowScene;

		public:
			SceneManager();
			~SceneManager();
			void Update();
			void Draw();
			void ChangeScene(SCENE NextScene) override;
		};
	}
}
