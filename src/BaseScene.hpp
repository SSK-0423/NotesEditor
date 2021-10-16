#pragma once
#include "IScene.hpp"

/*
* シーンの基底クラス
*/

namespace Engine
{
	namespace Scene
	{
		class ISceneChanger;

		class BaseScene : public IScene {
		protected:
			ISceneChanger* sceneChanger;

		public:
			BaseScene(ISceneChanger* changer);
			virtual ~BaseScene() {}
			virtual void Initialize() override {};
			virtual void Update() override {};
			virtual void Draw() override {};
			virtual void Finalize() override {};
		};
	}

}