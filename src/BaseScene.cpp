#include "BaseScene.hpp"
#include "DxLib.h"

namespace Game
{
	BaseScene::BaseScene(System::ISceneChanger* changer)
	{
		sceneChanger = changer;
	}
}