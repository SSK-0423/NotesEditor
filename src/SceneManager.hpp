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
			//シーン管理変数
			BaseScene* nowScene;
			// 次のシーン管理変数
			SCENE nextScene;

		public:
			SceneManager();
			void Update();
			void Draw();

			// ISceneChangerインターフェイス
			// 引数 nextScene にシーンを変更する
			void ChangeScene(SCENE NextScene) override;
		};
	}
}
