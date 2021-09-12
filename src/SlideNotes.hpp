#pragma once
#include "ShortNotes.hpp"
#include "CubicSpline.hpp"
#include <vector>

class SlideNotes : public Notes {
private:
	// 3���X�v���C����ԃN���X
	CubicSpline cubicSpline;			
	// �m�[�c���X�g
	std::vector<ShortNotes*> notesList;	
	// �`����W���X�g
	vector<float> dx_;					
	// �`����W���X�g
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