#pragma once

/*
* シーン変更のインターフェース
*/		

enum class SCENE
{
	SCENE_EDIT,
	SCENE_NONE
};

namespace Engine
{
	namespace Scene {

		class ISceneChanger {
		public:
			virtual ~ISceneChanger() = 0;
			virtual void ChangeScene(SCENE NextScene) = 0;
		};
	}

}