#include "BaseScene.hpp"
#include "ISceneChanger.hpp"
#include "DxLib.h"

Engine::Scene::BaseScene::BaseScene(ISceneChanger* changer)
{
	sceneChanger = changer;
}
