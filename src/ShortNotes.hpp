#pragma once
#include "Notes.hpp"

/*
* �V���[�g�m�[�c�N���X
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
		// �m�[�c�̉���
		static const int SHORTNOTESWIDTH;
		// �m�[�c�̏c��
		static const int SHORTNOTESHEIGHT;
		// �n���h�N���b�v�Đ����̃^�C�~���O����̋��e��
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