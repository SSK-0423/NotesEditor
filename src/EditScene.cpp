#include "EditScene.hpp"
#include "DxLib.h"

namespace NotesEditor
{
	EditScene::EditScene(Game::Scene::ISceneChanger* changer) : BaseScene(changer)
	{
		editorSceneCanvas.Init();
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
		editorSceneCanvas.Draw();
	}

}