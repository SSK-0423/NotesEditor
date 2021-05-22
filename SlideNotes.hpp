#pragma once
#include "Notes.hpp"
#include "ShortNotes.hpp"
#include <vector>
#include "CubicSpline.hpp"

class SlideNotes : public Notes {
private:
	CubicSpline cubicSpline;			//3次スプライン補間クラス
	std::vector<ShortNotes*> notesList;		//ノーツリスト
	vector<float> dx_;					//描画座標リスト
	vector<float> dy_;					//描画座標リスト
	void InitCubicSpline() noexcept;
public:
	SlideNotes(float& x, float& y, std::vector<ShortNotes*> list) noexcept;
	~SlideNotes() noexcept;
	void Draw() noexcept override;
	void SetNotesList(std::vector<ShortNotes*> notesList) noexcept;
	void DrawCurve() noexcept;
	void SetPoint() noexcept;
};