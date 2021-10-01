#pragma once
#include "BaseScene.hpp"
#include "EditorSceneCanvas.hpp"
#include "NotesEditorMusic.hpp"

namespace NotesEditor 
{

	class EditScene : public Engine::Scene::BaseScene{
	private:
		EditorSceneCanvas editorSceneCanvas;
		int laneHandle;
		//EditorCamera editorCamera
		//EditorCanvas editorCanvas;
		//Camera2D camera;
		//BarManager barManager;
		//NotesManager notesManager;
		//std::vector<std::vector<GameObject*>*> objList;

	public:
		EditScene(Engine::Scene::ISceneChanger* changer);
		void Update() override;
		void Draw() override;
	};
}