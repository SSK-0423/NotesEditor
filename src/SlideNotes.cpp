#include "SlideNotes.hpp"
#include "DxLib.h"
#include <math.h>

#define DRAWMODE 1;
#define INF 2000000;

SlideNotes::SlideNotes(std::vector<ShortNotes*> list) noexcept {
	notesList = list;
	timing = 0;
	width = CalcWidth();
	height = fabs(notesList.back()->collisionPos.y - notesList[0]->collisionPos.y);
	position.x = CalcColPosX();
	collisionPos.x = CalcColPosX();
	position.y = (notesList[0]->collisionPos.y + notesList.back()->collisionPos.y) / 2;
	collisionPos.y = (notesList[0]->collisionPos.y + notesList.back()->collisionPos.y) / 2;

	InitCubicSpline();
	SetPoint();
}

SlideNotes::~SlideNotes() noexcept {
	for (auto obj : notesList) {
		delete[] obj;
	}
	notesList.clear();
}

void SlideNotes::Update() noexcept {
	for (auto notes : notesList) {
		notes->SetPosition(position.x, position.y);
	}
}

void SlideNotes::Draw() noexcept {
	/*DrawBox(position.x - width / 2, position.y - height / 2,
		position.x + width / 2, position.y + height / 2,
		GetColor(0, 0, 255), true);*/
	DrawCurve();
}

void SlideNotes::SetNotesList(std::vector<ShortNotes*> list) noexcept
{
	std::copy(list.begin(), list.end(), notesList.begin());

	InitCubicSpline();
	SetPoint();
}

void SlideNotes::InitCubicSpline() noexcept
{

}

// x-y��y-x�ɕϊ������̂ŁAdx_ = dy_ dy = dx_
void SlideNotes::DrawCurve() noexcept {
	unsigned int slideColor = GetColor(255, 255, 0);
	unsigned int StartEndColor = GetColor(255, 192, 0);
	for (int i = 1; i < dx_.size() - 1; i++) {
#if DRAWMODE
		DrawBoxAA(dy_[i] + 40, position.y + (dx_[i] - dx_[0] + height / 2) + 1,
			dy_[i] - 40, position.y + (dx_[i] - dx_[0] + height / 2) - 1, slideColor, true);
#else
		DrawBoxAA(dy_[i] + 40, position.y + dx_[i] + 1 + notesList[notesList.size() - 1]->collisionPos.y / 2,
			dy_[i] - 40, position.y + dx_[i] - 1 + notesList[notesList.size() - 1]->collisionPos.y / 2, slideColor, true);
#endif 
	}

#if DRAWMODE
	//�n�_�ƏI�_
	DrawBoxAA(dy_[0] - 40, position.y + height / 2 - 5,
		dy_[0] + 40, position.y + height / 2 + 5, StartEndColor, true);
	DrawBoxAA(dy_.back() - 40, (position.y - height / 2) - 5,
		dy_.back() + 40, (position.y - height / 2) + 5, StartEndColor, true);

#else
	//�n�_�ƏI�_
	DrawBoxAA(dy_[0] + 40, position.y + dx_[0] + 5,
		dy_[0] - 40, position.y + dx_[0] - 5, StartEndColor, true);
	DrawBoxAA(dy_[dx_.size() - 1] + 40, position.y + dx_[dx_.size() - 1] + 5,
		dy_[dx_.size() - 1] - 40, position.y + dx_[dx_.size() - 1] - 5, StartEndColor, true);
#endif

	int x;
	int y;

	GetMousePoint(&x, &y);

	//DrawFormatString(800, 500, GetColor(0, 255, 0), "ColPosY:%f", this->collisionPos.y);
	//DrawFormatString(800, 525, GetColor(0, 255, 0), "positionY:%f", position.y);// + dx_[0] + 5);
	//DrawFormatString(800, 550, GetColor(0, 255, 0), "MouseX:%d,MouseY:%d", x, y);// + dx_[0] + 5);
	//DrawFormatString(800, 575, GetColor(0, 255, 0), "width:%d", width);// + dx_[0] + 5);
	//DrawFormatString(800, 600, GetColor(0, 255, 0), "height:%d", height);// + dx_[0] + 5);

	DrawBox(position.x - width / 2, position.y - height / 2, position.x + width / 2, position.y + height / 2, GetColor(255, 0, 0), false);
	DrawCircle(position.x, position.y, 10, GetColor(255, 255, 255), true);

	/*DrawBoxAA(notesList[0]->position.x + 40, notesList[0]->position.y + 5,
		notesList[0]->position.x - 40, notesList[0]->position.y - 5, StartEndColor, true);
	DrawBoxAA(notesList[notesList.size() - 1]->position.x + 40, notesList[notesList.size() - 1]->position.y + 5,
		notesList[notesList.size() - 1]->position.x - 40, notesList[notesList.size() - 1]->position.y - 5, StartEndColor, true);*/

}

void SlideNotes::SetPoint() noexcept {
	//�_�̍��W�i�[���X�g
	std::vector<vector<double>> p_;
	p_.resize(notesList.size());
	//�F
	unsigned int color = GetColor(0, 0, 255);

	//���ԓ_�̍��W����
	// y-x�̊֐��Ȃ̂�x��y���t�ɂ���
	for (int i = 0; i < notesList.size(); i++) {
		p_[i].push_back(notesList[i]->collisionPos.y);
		p_[i].push_back(notesList[i]->collisionPos.x);
	}

	//�X�v���C�����
	cubicSpline.cubicSpline(p_, p_.size());

	//�e�_�Ԃ̕�ԓ_��
	int split = 100;
	for (int i = 0; i < p_.size() - 1; i++) {
		split = fabs(p_[i + 1][0] - p_[i][0]) / 96 * 100;
		//2�_�Ԃ̋������ԓ_���Ŋ���
		float step = fabs(p_[i + 1][0] - p_[i][0]) / split;
		//dx_,dy_�ɕ�ԍ��W����
		for (int j = 0; j < split + 1; j++) {
			//x���W(y���W)���
			dx_.push_back(p_[i][0] - step * j);
			//y���W(x���W)���Ԋ֐���p���Čv�Z
			dy_.push_back(cubicSpline.interpolation(p_[i][0] - step * j, true));
			//dy_.push_back(cubicSpline.interpolation(step * j, true) - cubicSpline.interpolation(step * 0,true));
		}
	}

}

//width�v�Z
int SlideNotes::CalcWidth() noexcept {
	int max = -INF;
	int min = INF;

	for (auto notes : notesList) {
		//�ő�l
		if (notes->collisionPos.x > max) {
			max = notes->collisionPos.x;
		}
		//�ŏ��l
		if (notes->collisionPos.x < min) {
			min = notes->collisionPos.x;
		}
	}
	if (max == min) {
		return 100;
	}
	return abs(max - min);
}

//CollisionPosX�����߂�
int SlideNotes::CalcColPosX() noexcept {
	int max = -INF;
	int min = INF;

	for (auto notes : notesList) {
		//�ő�l
		if (notes->collisionPos.x > max) {
			max = notes->collisionPos.x;
		}
		//�ŏ��l
		if (notes->collisionPos.x < min) {
			min = notes->collisionPos.x;
		}
	}

	return (max + min) / 2;
}