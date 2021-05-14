#pragma once
#include "Notes.hpp"
#include "ShortNotes.hpp"
#include <vector>

class LongNotes : public Notes{
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
	void AddEndNotes(ShortNotes& end) noexcept;
	void SetObjSize(int w, int h) noexcept;
	void Draw() noexcept override;
};