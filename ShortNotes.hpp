#pragma once
#include "Notes.hpp"

class ShortNotes : public Notes {
protected:
	static int clapHandle;
private:
	void PlayClap() noexcept;
public:
	ShortNotes(float& x, float& y) noexcept;
	~ShortNotes() noexcept;
	void Draw() noexcept override;
};