#pragma once
#include "Notes.hpp"
#include "ShortNotes.hpp"
#include <vector>
#include "CubicSpline.hpp"

class SlideNotes : public Notes {
private:
	CubicSpline cubicSpline;			//3���X�v���C����ԃN���X
	std::vector<ShortNotes*> notesList;		//�m�[�c���X�g
	vector<float> dx_;					//�`����W���X�g
	vector<float> dy_;					//�`����W���X�g
	void InitCubicSpline() noexcept;
public:
	SlideNotes(float& x, float& y, std::vector<ShortNotes*> list) noexcept;
	~SlideNotes() noexcept;
	void Draw() noexcept override;
	void SetNotesList(std::vector<ShortNotes*> notesList) noexcept;
	void DrawCurve() noexcept;
	void SetPoint() noexcept;
};