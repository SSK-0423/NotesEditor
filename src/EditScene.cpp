#include "EditScene.hpp"
#include "WindowSize.hpp"
#include "DxLib.h"

namespace NotesEditor
{
	EditScene::EditScene(Engine::Scene::ISceneChanger* changer) : BaseScene(changer)
	{
		editorSceneCanvas.Init();
		laneHandle = LoadGraph("image/Lane.png");
	}

	void EditScene::Update()
	{
		editorSceneCanvas.Update();
		//camera.Update();
		//editorCanvas.Update();
		//barManager.Update();
		//notesManager.Update();
	}

	void EditScene::Draw()
	{
		DrawRotaGraph(WINDOW_SIZE_WIDTH / 2, WINDOW_SIZE_HEIGHT / 2, 1.01, 0, laneHandle, true, false);
		editorSceneCanvas.Draw();
	}

}