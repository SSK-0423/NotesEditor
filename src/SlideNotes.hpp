#pragma once
#include "ShortNotes.hpp"
#include "CubicSpline.hpp"
#include "Vector2.hpp"
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
	// width�v�Z
	int CalcWidth() noexcept;
	// CollisionPosX�����߂�
	int CalcColPosX() noexcept;
	// CollisionPos�̍ő�l�擾
	int GetMaxColPosX();
	// CollsionPos�̍ŏ��l�擾
	int GetMinColPosX();
	// ��ԓ_�Z�b�g
	void SetInterpolationPoint(std::vector<vector<double>>& p_, float step, int splitNum, int i);
	// ��ԓ_�v�Z
	Vector2<float> CalcInterpolationPoint(std::vector<vector<double>>& p_, float step, int splitNum, int i, int j);
	// �J�[�u�̕`��
	void DrawCurve();
	// �n�_�ƏI�_�̕`��
	void DrawStartEnd();
	// �f�o�b�O�p�`��
	void DebugDraw();
	// ���ԓ_�Z�b�g
	void SetPoint() noexcept;
	// ������
	void Init();
public:
	SlideNotes(std::vector<ShortNotes*> list) noexcept;
	~SlideNotes() noexcept;
	void Update() noexcept override;
	void Draw() noexcept override;
	void SetNotesList(std::vector<ShortNotes*> notesList) noexcept;
};