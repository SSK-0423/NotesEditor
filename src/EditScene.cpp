#include "EditScene.hpp"

namespace NotesEditor
{
	EditScene::EditScene(Game::System::ISceneChanger* changer) : BaseScene(changer)
	{
	}

	void EditScene::Update()
	{
		//camera.Update();
		//editorCanvas.Update();
		//barManager.Update();
		//notesManager.Update();
	}

	void EditScene::Draw()
	{

	}

	void NotesEditor::EditScene::Input(const Game::Input::InputDeviceContainer& inputDeviceContainer)
	{
	}

}