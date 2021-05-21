#pragma once
#include "Notes.hpp"

class ShortNotes : public Notes {
protected:
	//static int clapHandle;
private:
	int clapHandle;
	void PlayClap() noexcept;
public:
	ShortNotes(float& x, float& y) noexcept;
	~ShortNotes() noexcept;
	void Update() noexcept override;
	void Draw() noexcept override;
};