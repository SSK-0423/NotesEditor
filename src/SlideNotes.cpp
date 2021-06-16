#include "SlideNotes.hpp"
#include "DxLib.h"
#include <math.h>

SlideNotes::SlideNotes(float& x, float& y, std::vector<ShortNotes*> list) noexcept {
	timing = 0;
	width = 100;
	height = fabs(list[list.size() - 1]->collisionPos.y - list[0]->collisionPos.y);
	position.x = 512;
	position.y = list[list.size() - 1]->collisionPos.y - list[0]->collisionPos.y;
	collisionPos.x = 512;
	collisionPos.y = list[list.size() - 1]->collisionPos.y - list[0]->collisionPos.y;

	notesList = list;
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

// x-yをy-xに変換したので、dx_ = dy_ dy = dx_
void SlideNotes::DrawCurve() noexcept {
	unsigned int slideColor = GetColor(0, 0, 255);
	unsigned int StartEndColor = GetColor(0, 128, 255);
	for (int i = 1; i < dx_.size() - 1; i++) {
		DrawBoxAA(dy_[i] + 40, position.y + dx_[i] + 1 - notesList[notesList.size() - 1]->collisionPos.y,
			dy_[i] - 40, position.y + dx_[i] - 1 - notesList[notesList.size() - 1]->collisionPos.y, slideColor, true);
	}

	//始点と終点
	DrawBoxAA(dy_[0] + 40, position.y + dx_[0] + 5,
		dy_[0] - 40, position.y + dx_[0] - 5, StartEndColor, true);
	DrawBoxAA(dy_[dx_.size() - 1] + 40, position.y + dx_[dx_.size() - 1] + 5,
		dy_[dx_.size() - 1] - 40, position.y + dx_[dx_.size() - 1] - 5, StartEndColor, true);

	/*DrawBoxAA(notesList[0]->position.x + 40, notesList[0]->position.y + 5,
		notesList[0]->position.x - 40, notesList[0]->position.y - 5, StartEndColor, true);
	DrawBoxAA(notesList[notesList.size() - 1]->position.x + 40, notesList[notesList.size() - 1]->position.y + 5,
		notesList[notesList.size() - 1]->position.x - 40, notesList[notesList.size() - 1]->position.y - 5, StartEndColor, true);*/

}

void SlideNotes::SetPoint() noexcept {
	//点の座標格納リスト
	std::vector<vector<double>> p_;
	p_.resize(notesList.size());
	//色
	unsigned int color = GetColor(0, 0, 255);

	for (int i = 0; i < notesList.size(); i++) {
		p_[i].push_back(notesList[i]->collisionPos.y);
		p_[i].push_back(notesList[i]->collisionPos.x);
	}

	//スプライン補間
	cubicSpline.cubicSpline(p_, p_.size());
	//各点間の補間点数
	int split = 100;
	for (int i = 0; i < p_.size() - 1; i++) {
		//2点間の距離を補間点数で割る
		float step = fabs(p_[i + 1][0] - p_[i][0]) / split;
		//dx_,dxy_に補間座標を代入
		for (int j = 0; j < split; j++) {
			//x座標(y座標)代入
			dx_.push_back(p_[i][0] - step * j);
			//y座標(x座標)を補間関数を用いて計算
			dy_.push_back(cubicSpline.interpolation(p_[i][0] - step * j, true));
			//dy_.push_back(cubicSpline.interpolation(step * j, true) - cubicSpline.interpolation(step * 0,true));
		}
	}
}