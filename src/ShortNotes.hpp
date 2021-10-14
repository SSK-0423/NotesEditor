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

		Color color;

		void PlayClap();
		// ノーツ描画
		void DrawNotes();
		// デバッグ用の描画
		void DebugDraw();

	public:
		// ノーツの横幅
		static const int SHORTNOTESWIDTH;
		// ノーツの縦幅
		static const int SHORTNOTESHEIGHT;
		// タイミングずれの許容幅
		static float playRange;

		ShortNotes(const NotesData& notesData);
		~ShortNotes();
		NOTESTYPE GetNotesType();
		bool Collision(float x, float y) override;
		void Update() override;
		void Draw() override;
		void SetColor(Color c);
	};
}