#pragma once
#include "Notes.hpp"

/*
* ショートノーツクラス
*/

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
		void DrawNotes();
		void DebugDraw();

	public:
		// ノーツの横幅
		static const int SHORTNOTESWIDTH;
		// ノーツの縦幅
		static const int SHORTNOTESHEIGHT;
		// ハンドクラップ再生時のタイミングずれの許容幅
		static const float playRange;

		ShortNotes(const NotesData& notesData);
		~ShortNotes();
		void Update() override;
		void Draw() override;
		void ChangedScale(float size, bool isScaleUp) override;
		bool Collision(float x, float y) override;
		NOTESTYPE GetNotesType() override;
		void SetColor(Color c);
	};
}