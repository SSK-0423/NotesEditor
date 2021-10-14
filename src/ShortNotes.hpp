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
		// �m�[�c�`��
		void DrawNotes();
		// �f�o�b�O�p�̕`��
		void DebugDraw();

	public:
		// �m�[�c�̉���
		static const int SHORTNOTESWIDTH;
		// �m�[�c�̏c��
		static const int SHORTNOTESHEIGHT;
		// �^�C�~���O����̋��e��
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