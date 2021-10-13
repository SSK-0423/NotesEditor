#pragma once
#include "ShortNotes.hpp"
#include "CubicSpline.hpp"
#include "Vector2.hpp"
#include "GameSymbol.hpp"
#include <vector>

namespace NotesEditor
{
	class SlideNotes : public Notes {
	private:
		// 3���X�v���C����ԃN���X
		CubicSpline cubicSpline;
		// �m�[�c���X�g
		std::vector<ShortNotes*> notesList;
		//
		Color notesColor;
		Color lineColor;

		// �`����W���X�g
		vector<float> dx_;
		// �`����W���X�g
		vector<float> dy_;
		// width�v�Z
		float CalcWidth();
		// height�v�Z
		float CalcHeight();
		// �n�_����I�_�m�[�c�܂ł�x���W�̍ő�l�擾
		float GetMaxPosX();
		// �n�_����I�_�m�[�c�܂ł�x���W�̍ŏ��l�擾
		float GetMinPosX();
		// ��ԓ_�Z�b�g
		void SetInterpolationPoint(std::vector<vector<double>>& p_, float step, int splitNum, int i);
		// ��ԓ_�v�Z
		Vector2<float> CalcInterpolationPoint(std::vector<vector<double>>& p_, float step, int splitNum, int i, int j);
		void DrawCurve();
		void DebugDraw();
		// ���ԓ_�Z�b�g
		void SetPoint();
		// ������
		void Init();

	public:
		SlideNotes(std::vector<ShortNotes*> list);
		~SlideNotes();
		void PutComplete();
		void AddNotes(ShortNotes& notes);
		bool Collision(float x, float y);
		NOTESTYPE GetNotesType() override;
		void Update() override;
		void Draw() override;
		std::vector<ShortNotes*> GetChildNotesList();
	};
}