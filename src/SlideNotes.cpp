#include "SlideNotes.hpp"
#include "Transform.hpp"
#include "BoxCollider.hpp"
#include "PointWithPolygon.hpp"
#include "DxLib.h"
#include <math.h>

#define DRAWMODE 1;
const float INF = 2000000.f;

NotesEditor::SlideNotes::SlideNotes(std::vector<ShortNotes*> list)
{
	notesList = list;

	collider = new Engine::Components::BoxCollider(*transform);
	collision = new Engine::Collision::PointWithPolygon();
	Init();
}

NotesEditor::SlideNotes::~SlideNotes()
{
}

void NotesEditor::SlideNotes::AddNotes(ShortNotes& notes)
{
	notesList.push_back(&notes);
	Init();
}

bool NotesEditor::SlideNotes::Collision(float x, float y)
{
	if (collision->Collision(x, y, *collider))
		return true;

	for (auto notes : notesList)
	{
		if (notes->Collision(x, y))
			return true;
	}

	return false;
}

NotesEditor::NOTESTYPE NotesEditor::SlideNotes::GetNotesType()
{
	return NOTESTYPE::SLIDE_NOTES;
}

void NotesEditor::SlideNotes::Update()
{
	for (auto notes : notesList)
	{
		Engine::Components::Position notesScreenPos;
		notesScreenPos.x = notes->GetTransform().GetPosition().x;
		notesScreenPos.y = screenPos->y + (notes->GetTransform().GetPosition().y - transform->GetPosition().y);
		notes->UpdateScreenPos(notesScreenPos);
		notes->Update();
	}
}

void NotesEditor::SlideNotes::Draw()
{
	if (notesList.size() >= 4)
		DrawCurve();
	for (auto notes : notesList)
	{
		notes->Draw();
	}
}

void NotesEditor::SlideNotes::SetNotesList(std::vector<ShortNotes*> notesList)
{
}

float NotesEditor::SlideNotes::CalcWidth()
{
	float max = GetMaxPosX();
	float min = GetMinPosX();
	if (max == min)
		return ShortNotes::SHORTNOTESWIDTH;
	return fabsf(max - min);
}

float NotesEditor::SlideNotes::CalcHeight()
{
	float startNotesPosY = notesList[0]->GetTransform().GetPosition().y;
	float endNotesPosY = notesList.back()->GetTransform().GetPosition().y;
	if (startNotesPosY == endNotesPosY)
		return ShortNotes::SHORTNOTESHEIGHT;
	return fabsf(endNotesPosY - startNotesPosY);
}

float NotesEditor::SlideNotes::GetMaxPosX()
{
	float max = -INF;
	for (auto notes : notesList)
	{
		float notesPosX = notes->GetTransform().GetPosition().x;
		//最大値
		if (notesPosX > max)
			max = notesPosX;
	}
	return max;
}

float NotesEditor::SlideNotes::GetMinPosX()
{
	float min = INF;
	for (auto notes : notesList)
	{
		float notesPosX = notes->GetTransform().GetPosition().x;
		//最小値
		if (notesPosX < min)
			min = notesPosX;
	}
	return min;
}

void NotesEditor::SlideNotes::SetInterpolationPoint(std::vector<vector<double>>& p_, float step, int splitNum, int i)
{
	for (int j = 0; j < splitNum + 1; j++)
	{
		Vector2<float> vec = CalcInterpolationPoint(p_, step, splitNum, i, j);
		// x座標(y座標)代入
		dx_.push_back(vec.y);
		// y座標(x座標)を補間関数を用いて計算
		dy_.push_back(vec.x);
	}
}

Vector2<float> NotesEditor::SlideNotes::CalcInterpolationPoint(std::vector<vector<double>>& p_, float step, int splitNum, int i, int j)
{
	float x = cubicSpline.interpolation(p_[i][0] - step * static_cast<float>(j), true);
	float y = p_[i][0] - step * static_cast<float>(j);
	Vector2<float> vec;
	vec.x = x;
	vec.y = y;
	return vec;
}

void NotesEditor::SlideNotes::DrawCurve()
{
	Engine::Components::Position position = *screenPos;
	Engine::Components::Size size = transform->GetSize();

	unsigned int slideColor = GetColor(255, 255, 0);
	unsigned int StartEndColor = GetColor(255, 192, 0);
	for (int i = 0; i < dx_.size() - 1; i++) {
#if DRAWMODE
		// dx_[i] - dx_[0]
		DrawBoxAA(dy_[i] + 40, position.y + (dx_[i] - dx_[0] + size.height / 2) + 1,
			dy_[i + 1] - 40, position.y + (dx_[i + 1] - dx_[0] + size.height / 2) - 1, slideColor, true);
#else
		DrawBoxAA(dy_[i] + 40, position.y + dx_[i] + 1 + notesList[notesList.size() - 1]->GetTransform().GetPosition().y / 2.f,
			dy_[i] - 40, position.y + dx_[i] - 1 + notesList[notesList.size() - 1]->GetTransform().GetPosition().y / 2.f, slideColor, true);
#endif 
	}

#if DRAWMODE
	//始点と終点
	//DrawBoxAA(dy_[0] - 40, position.y + height / 2 - 5,
	//	dy_[0] + 40, position.y + height / 2 + 5, StartEndColor, true);
	//DrawBoxAA(dy_.back() - 40, (position.y - height / 2) - 5,
	//	dy_.back() + 40, (position.y - height / 2) + 5, StartEndColor, true);

#else
	//始点と終点
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

	DrawBoxAA(position.x - size.width / 2.f, position.y - size.height / 2.f, position.x + size.width / 2.f, position.y + size.height / 2.f, GetColor(255, 0, 0), false);
	DrawCircle(position.x, position.y, 10, GetColor(255, 255, 255), true);

	/*DrawBoxAA(notesList[0]->position.x + 40, notesList[0]->position.y + 5,
		notesList[0]->position.x - 40, notesList[0]->position.y - 5, StartEndColor, true);
	DrawBoxAA(notesList[notesList.size() - 1]->position.x + 40, notesList[notesList.size() - 1]->position.y + 5,
		notesList[notesList.size() - 1]->position.x - 40, notesList[notesList.size() - 1]->position.y - 5, StartEndColor, true);*/

}

void NotesEditor::SlideNotes::DebugDraw()
{
}

void NotesEditor::SlideNotes::SetPoint()
{
	// 点の座標格納リスト
	std::vector<vector<double>> p_;
	p_.resize(notesList.size());
	// 色
	Color color = GetColor(0, 0, 255);

	// 中間点の座標を代入
	// y-xの関数なのでxとyを逆にする
	for (int i = 0; i < notesList.size(); i++)
	{
		p_[i].push_back(notesList[i]->GetTransform().GetPosition().y);
		p_[i].push_back(notesList[i]->GetTransform().GetPosition().x);
	}

	//スプライン補間
	cubicSpline.cubicSpline(p_, p_.size());
	//各点間の補間点数
	int splitNum;

	for (int i = 0; i < p_.size() - 1; i++)
	{
		//// x座標が同じならリソース削減のために分割数を1にする
		if (p_[i][1] == p_[i + 1][1])
		{
			splitNum = 1;
		}
		else
		{
			// 分割数の調整
			splitNum = fabs(p_[i + 1][0] - p_[i][0]);
		}
		// 分割数の調整
		//splitNum = fabs(p_[i + 1][0] - p_[i][0]) / 96 * 96;
		// 2点間の距離を補間点数で割る
		float step = fabs(p_[i + 1][0] - p_[i][0]) / splitNum;
		SetInterpolationPoint(p_, step, splitNum, i);
	}
}

void NotesEditor::SlideNotes::Init()
{
	float width = CalcWidth();
	float height = CalcHeight();
	float x = (GetMaxPosX() + GetMinPosX()) / 2.f;
	float y = (notesList[0]->GetTransform().GetPosition().y + notesList.back()->GetTransform().GetPosition().y) / 2.f;

	transform->SetPosition(x, y);
	transform->SetSize(width, height);

	collider->Update();
	if (notesList.size() >= 4)
	{
		// スプライン補間結果初期化
		cubicSpline.Init();
		// 補間点リストを初期化
		dx_.clear();
		dx_.shrink_to_fit();
		dy_.clear();
		dy_.shrink_to_fit();
		SetPoint();
	}
}

