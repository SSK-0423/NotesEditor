#pragma once
#include "BaseScene.hpp"
#include "EditorSceneCanvas.hpp"
#include "Camera2D.hpp"
#include "TestObject.h"
#include "Bar.hpp"

namespace Engine
{
	class GameObject;
}

namespace NotesEditor
{
	class NotesManager;
	class LaneManager;
	class BarManager;
	class NotesEditorMusic;

	class EditScene : public Engine::Scene::BaseScene {
	private:
		EditorSceneCanvas editorSceneCanvas;
		int laneHandle;
		//EditorCamera editorCamera
		Engine::Camera2D camera;
		NotesEditorMusic& notesEditorMusic;
		NotesManager& notesManager;
		LaneManager& laneManager;
		BarManager& barManager;
		std::vector<Engine::GameObject*> allObjList;
		
		void Input();
		void OnMusicLoaded();
		void DeleteObj();
		void PutNotes();
		void RemoveNotes();
		void DecidePutPos();
		float CalcJudgeTiming(float y);
		void DebugDraw();
		void DebugPutNotes();

	public:
		EditScene(Engine::Scene::ISceneChanger* changer);
		void Init() override;
		void Update() override;
		void Draw() override;
	};
}