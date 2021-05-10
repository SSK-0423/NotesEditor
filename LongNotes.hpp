#pragma once
#include "Notes.hpp"
#include <vector>

class LongNotes : public Notes{
private:
	static unsigned int color;
	Notes* startNotes;
	Notes* endNotes;
public:
	LongNotes() noexcept;
	LongNotes(Notes& start, Notes& end);
	~LongNotes() noexcept;
	void Draw() noexcept override;
};