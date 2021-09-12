#pragma once
#include "ShortNotes.hpp"
#include "CubicSpline.hpp"
#include <vector>

class SlideNotes : public Notes {
private:
	// 3次スプライン補間クラス
	CubicSpline cubicSpline;			
	// ノーツリスト
	std::vector<ShortNotes*> notesList;	
	// 描画座標リスト
	vector<float> dx_;					
	// 描画座標リスト
	vector<float> dy_;
	// 
	int CalcWidth() noexcept;
	int CalcColPosX() noexcept;
	int GetMaxColPosX();
	int GetMinColPosX();
	void SetInterpolationPoint(std::vector<vector<double>>& p_);
	void CalcInterpolationPoint(std::vector<vector<double>>& p_,int splitNum, int index);
public:
	SlideNotes(std::vector<ShortNotes*> list) noexcept;
	~SlideNotes() noexcept;
	void Update() noexcept override;
	void Draw() noexcept override;
	void SetNotesList(std::vector<ShortNotes*> notesList) noexcept;
	void DrawCurve() noexcept;
	void SetPoint() noexcept;
};