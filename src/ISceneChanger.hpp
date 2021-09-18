#pragma once

typedef enum 
{
	SCENE_EDIT,
	SCENE_NONE
} SCENE;

namespace Game {

	namespace System {

		//シーンを変更するためのインターフェイスクラス
		class ISceneChanger{
		public:
			virtual ~ISceneChanger() = 0;
			//指定シーンに変更する
			virtual void ChangeScene(SCENE NextScene) = 0;
		};
	}
}