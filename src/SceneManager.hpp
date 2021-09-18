#pragma once
#include "ISceneChanger.hpp"
#include "BaseScene.hpp"
#include "InputDeviceContainer.hpp"

namespace Game {

	namespace System {

		class SceneManager : public ISceneChanger{
		private:
			//シーン管理変数
			BaseScene* nowScene;	
			// 次のシーン管理変数
			SCENE nextScene;		

		public:
			SceneManager();
			void Update();
			void Draw();
			void Input(const Input::InputDeviceContainer& inputDeviceContainer);

			// ISceneChangerインターフェイス
			// 引数 nextScene にシーンを変更する
			void ChangeScene(SCENE NextScene) override;
		};
	}
}