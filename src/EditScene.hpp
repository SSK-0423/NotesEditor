#pragma once
#include "BaseScene.hpp"
#include "Texture.hpp"

namespace NotesEditor {

	class EditScene : public Game::BaseScene{
	private:
		//EditorCamera editorCamera
		//EditorCanvas editorCanvas;
		//Camera2D camera;
		//BarManager barManager;
		//NotesManager notesManager;
		//std::vector<std::vector<GameObject*>*> objList;

	public:
		EditScene(Game::System::ISceneChanger* changer);
		void Update() override;
		void Draw() override;
		void Input(const Game::Input::InputDeviceContainer& inputDeviceContainer) override;
	};
}