#pragma once
#include "Notes.hpp"

namespace NotesEditor
{
	class ShortNotes : public Notes {
	private:
		Audio clapHandle;
		Color color;
		void PlayClap() noexcept;
		// �m�[�c�`��
		void DrawNotes();
		// �f�o�b�O�p�̕`��
		void DebugDraw();
	public:
		// �m�[�c�̉���
		static const int SHORTNOTESWIDTH;
		// �m�[�c�̏c��
		static const int SHORTNOTESHEIGHT;

		ShortNotes(float& x, float& y) noexcept;
		~ShortNotes() noexcept;
		void Update() noexcept override;
		void Draw() noexcept override;
		void SetColor(Color c);
		Color GetNotesColor();
	};
}