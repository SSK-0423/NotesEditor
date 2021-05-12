#pragma once
#include "Notes.hpp"
#include <vector>

class LongNotes : public Notes{
private:
	static unsigned int color;
	Notes* startNotes;
	Notes* endNotes;
public:
	LongNotes(float& x, float& y) noexcept;
	LongNotes(Notes& start, Notes& end) noexcept;
	~LongNotes() noexcept;
	void Draw() noexcept override;
};