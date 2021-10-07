#pragma once
#include "BaseScene.hpp"
#include "EditorSceneCanvas.hpp"
#include "Camera2D.hpp"
#include "NotesEditorMusic.hpp"
#include "BarManager.hpp"
#include "TestObject.h"
#include "NotesManager.hpp"
#include "Bar.hpp"


namespace Engine
{
	class GameObject;
}
namespace NotesEditor
{

	class EditScene : public Engine::Scene::BaseScene {
	private:
		EditorSceneCanvas editorSceneCanvas;
		int laneHandle;
		//EditorCamera editorCamera
		Engine::Camera2D camera;
		//NotesManager notesManager;
		std::vector<Engine::GameObject*> allObjList;

		void Input();
		void OnMusicLoaded();
	public:
		EditScene(Engine::Scene::ISceneChanger* changer);
		void Init() override;
		void Update() override;
		void Draw() override;
	};
}