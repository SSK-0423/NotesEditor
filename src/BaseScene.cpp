#include "BaseScene.hpp"
#include "ISceneChanger.hpp"
#include "DxLib.h"

Game::Scene::BaseScene::BaseScene(ISceneChanger* changer)
{
	sceneChanger = changer;
}
