#pragma once
#include "Notes.hpp"
#include "ShortNotes.hpp"
#include <vector>

class LongNotes : public Notes{
private:
	// ノーツの色
	static unsigned int color;
	//始点ノーツ
	ShortNotes* startNotes;
	// 終点ノーツ
	ShortNotes* endNotes;
public:
	LongNotes(ShortNotes& start) noexcept;
	LongNotes(ShortNotes& start, ShortNotes& end) noexcept;
	~LongNotes() noexcept;
	void AddEndNotes(ShortNotes& end) noexcept;
	void SetObjSize(int w, int h) noexcept;
	void Draw() noexcept override;
};