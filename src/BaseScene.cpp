#include "BaseScene.hpp"
#include "ISceneChanger.hpp"
#include "DxLib.h"

BaseScene::BaseScene(ISceneChanger* changer)
{
	sceneChanger = changer;
}
