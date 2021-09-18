#include "EditScene.hpp"
#include "DxLib.h"

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
		if (inputDeviceContainer.GetMouse().IsPressKey(Game::Input::Mouse::LEFT_CLICK))
			DrawFormatString(0, 20, GetColor(0, 255, 0), "���N���b�N");
		if (inputDeviceContainer.GetMouse().IsPressKey(Game::Input::Mouse::RIGHT_CLICK))
			DrawFormatString(0, 40, GetColor(0, 255, 0), "�E�N���b�N");
		if (inputDeviceContainer.GetMouse().IsReleaseKey(Game::Input::Mouse::LEFT_CLICK))
			DrawFormatString(0, 60, GetColor(0, 255, 0), "���N���b�N�������ꂽ");
		if (inputDeviceContainer.GetMouse().IsReleaseKey(Game::Input::Mouse::RIGHT_CLICK))
			DrawFormatString(0, 80, GetColor(0, 255, 0), "�E�N���b�N�������ꂽ");
		
		if (inputDeviceContainer.GetKeyboard().IsPressKey(KEY_INPUT_W))
			DrawFormatString(0, 100, GetColor(0, 255, 0), "W�L�[");
		if (inputDeviceContainer.GetKeyboard().IsReleaseKey(KEY_INPUT_W))
			DrawFormatString(0, 120, GetColor(0, 255, 0), "W�L�[�������ꂽ");
	}

}