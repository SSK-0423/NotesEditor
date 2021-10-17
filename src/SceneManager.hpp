#pragma once
#include "ISceneChanger.hpp"
#include "BaseScene.hpp"

/*
	各シーンの実行とシーン遷移を担うクラス
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
