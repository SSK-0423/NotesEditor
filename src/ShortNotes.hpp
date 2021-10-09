#pragma once
#include "Notes.hpp"

namespace Engine
{
	namespace Components
	{
		class AudioSource;
		class ICollider;
	}
	namespace Collision
	{
		class PointWithPolygon;
	}
}

namespace NotesEditor
{
	struct NotesData;
	class NotesEditorMusic;

	class ShortNotes : public Notes {
	private:
		static NotesEditorMusic& notesEditorMusic;
		Engine::Components::AudioSource* handClap;
		Engine::Components::ICollider* collider;
		Engine::Collision::PointWithPolygon* collision;

		Color color;

		void PlayClap() ;
		// ノーツ描画
		void DrawNotes();
		// デバッグ用の描画
		void DebugDraw();
	public:
		// ノーツの横幅
		static const int SHORTNOTESWIDTH;
		// ノーツの縦幅
		static const int SHORTNOTESHEIGHT;
		//
		static float playRange;

		ShortNotes(float x, float y);
		ShortNotes(const NotesData& notesData);
		~ShortNotes() ;
		void Update()  override;
		void Draw()  override;
		void SetColor(Color c);
		Color GetNotesColor();
	};
}