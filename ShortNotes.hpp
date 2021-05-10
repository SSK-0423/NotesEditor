#pragma once
#include "Notes.hpp"

class ShortNotes : public Notes {
private:
public:
	ShortNotes() noexcept;
	~ShortNotes() noexcept;
	void Draw() noexcept override;
};