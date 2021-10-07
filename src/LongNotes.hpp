#pragma once
#include "Notes.hpp"
#include "ShortNotes.hpp"
#include <vector>

namespace NotesEditor
{
	class LongNotes : public Notes {
	private:
		// �m�[�c�̐F
		static unsigned int color;
		//�n�_�m�[�c
		ShortNotes* startNotes;
		// �I�_�m�[�c
		ShortNotes* endNotes;
	public:
		LongNotes(ShortNotes& start) noexcept;
		LongNotes(ShortNotes& start, ShortNotes& end) noexcept;
		~LongNotes() noexcept;
		void SetStartNotes(ShortNotes& start) noexcept;
		void SetEndNotes(ShortNotes& end) noexcept;
		void SetObjSize(int w, int h) noexcept;
		void Update() noexcept override;
		void Draw() noexcept override;
	};
}