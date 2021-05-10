#pragma once
#include "Notes.hpp"
#include <vector>
class SlideNotes : public Notes{
private:
	std::vector<Notes*> notes;
public:
	SlideNotes() noexcept;
	~SlideNotes() noexcept;
	void Draw() noexcept override;
};