#pragma once
#include "BaseScene.hpp"
#include "Camera2D.hpp"
#include "Bar.hpp"
#include "EditorSceneCanvas.hpp"
#include "GameUtility.hpp"

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
	class FumenJsonGenerator;
	class FumenJsonLoader;

	class EditScene : public Engine::Scene::BaseScene {
	private:
		Image laneHandle;
		EditorSceneCanvas editorSceneCanvas;
		Engine::Camera2D camera;
		NotesEditorMusic& notesEditorMusic;
		NotesManager& notesManager;
		LaneManager& laneManager;
		BarManager& barManager;
		FumenJsonGenerator& fumenJsonGenerator;
		FumenJsonLoader& fumenJsonLoader;
		std::vector<Engine::GameObject*> allObjList;
		
		void Input();
		void OnMusicLoaded();
		void DeleteObj();
		void PutNotes();
		void RemoveNotes();
		float CalcJudgeTiming(float y);

	public:
		EditScene(Engine::Scene::ISceneChanger* changer);
		void Initialize() override;
		void Update() override;
		void Draw() override;
		void Finalize() override;
	};
}