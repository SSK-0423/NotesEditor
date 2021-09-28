#pragma once
#include "BaseScene.hpp"
#include "Texture.hpp"
#include "EditorSceneCanvas.hpp"

namespace NotesEditor 
{

	class EditScene : public Scene::BaseScene{
	private:
		EditorSceneCanvas editorSceneCanvas;

		//EditorCamera editorCamera
		//EditorCanvas editorCanvas;
		//Camera2D camera;
		//BarManager barManager;
		//NotesManager notesManager;
		//std::vector<std::vector<GameObject*>*> objList;

	public:
		EditScene(Scene::ISceneChanger* changer);
		void Update() override;
		void Draw() override;
	};
}