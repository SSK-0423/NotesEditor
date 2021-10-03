#pragma once
#include "BaseScene.hpp"
#include "EditorSceneCanvas.hpp"
#include "Camera2D.hpp"
#include "NotesEditorMusic.hpp"
#include "TestObject.h"

namespace Engine
{
	class GameObject;
}
namespace NotesEditor 
{

	class EditScene : public Engine::Scene::BaseScene{
	private:
		EditorSceneCanvas editorSceneCanvas;
		int laneHandle;
		//EditorCamera editorCamera
		//EditorCanvas editorCanvas;
		Engine::Camera2D camera;
		//BarManager barManager;
		//NotesManager notesManager;
		std::vector<std::vector<Engine::GameObject*>*> objList;
		TestObject obj;
	public:
		EditScene(Engine::Scene::ISceneChanger* changer);
		void Update() override;
		void Draw() override;
	};
}