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
		Image backgroundHandle;
		EditorSceneCanvas editorSceneCanvas;
		Engine::Camera2D camera;
		NotesEditorMusic& notesEditorMusic;
		NotesManager& notesManager;
		LaneManager& laneManager;
		BarManager& barManager;
		FumenJsonGenerator& fumenJsonGenerator;
		FumenJsonLoader& fumenJsonLoader;
		std::vector<Engine::GameObject*> allObjList;
		
		static const float MAXSCALE;
		static const float MINSCALE;
		static const float SCALEUNIT;
		float scale;
		
		void Input();
		void OnMusicLoaded();
		void PutNotes();
		void RemoveNotes();
		float CalcJudgeTiming(float y);
		int CalcLineNum(long long totalTime, float bpm, float beat);
		int CalcBarNum(long long totalTime, float bpm, float beat);
		void UpdateStartMusicTime();
		void DrawLaneBackground();
		void OnChangedScale(int mouseWheelRotVol);

	public:
		EditScene(Engine::Scene::ISceneChanger* changer);
		~EditScene();
		void Initialize() override;
		void Update() override;
		void Draw() override;
		void Finalize() override;
	};
}