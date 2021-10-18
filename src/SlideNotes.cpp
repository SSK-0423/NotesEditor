#include "SlideNotes.hpp"
#include "Transform.hpp"
#include "BoxCollider.hpp"
#include "PointWithPolygon.hpp"
#include "DxLib.h"
#include "NotesColor.hpp"
#include <math.h>

#define DRAWMODE 1;

const float INF = 2000000.f;

NotesEditor::SlideNotes::SlideNotes(std::vector<ShortNotes*> list)
{
	timing = list[0]->GetTiming();
	lane = list[0]->GetLane();
	barNum = list[0]->GetBarNum();
	lineNum = list[0]->GetLineNum();
	notesList = list;
	notesColor = NotesColor::puttingNotesColor;
	lineColor = NotesColor::puttingLineColor;

	Init();
}

NotesEditor::SlideNotes::~SlideNotes()
{
	for (auto& notes : notesList)
	{
		delete notes;
	}
}

void NotesEditor::SlideNotes::PutComplete()
{
	notesColor = NotesColor::slideNotesColor;
	lineColor = NotesColor::slideNotesLineColor;
	for (auto notes : notesList)
	{
		notes->SetColor(notesColor);
	}
}

void NotesEditor::SlideNotes::AddNotes(ShortNotes& notes)
{
	notesList.push_back(&notes);
	Init();
}

bool NotesEditor::SlideNotes::Collision(float x, float y)
{
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
		notes->Draw();

}

void NotesEditor::SlideNotes::ChangedTransformByScale(float scale, bool isScaleUp)
{
	for (auto notes : notesList)
		notes->ChangedTransformByScale(scale, isScaleUp);

	transform->Scaling(1.f, scale);
	// ������()
	Init();
	//�X�P�[��1�{�̎��̃T�C�Y��ݒ肷��
	Engine::Components::Size size = transform->GetSize();
	transform->SetSize(size.width, size.height / scale);
}

std::vector<NotesEditor::ShortNotes*> NotesEditor::SlideNotes::GetChildNotesList()
{
	return notesList;
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
		//�ő�l
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
		//�ŏ��l
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
		// x���W(y���W)���
		dx_.push_back(vec.y);
		// y���W(x���W)���Ԋ֐���p���Čv�Z
		dy_.push_back(vec.x);
	}
}

Vector2<float> NotesEditor::SlideNotes::CalcInterpolationPoint(std::vector<vector<double>>& p_, float step, int splitNum, int i, int j)
{
	float x = static_cast<float>(cubicSpline.interpolation(p_[i][0] - step * static_cast<double>(j), true));
	float y = static_cast<float>(p_[i][0] - step * static_cast<double>(j));
	Vector2<float> vec;
	vec.x = x;
	vec.y = y;
	return vec;
}

/*
* �������{��1�{�̎��̍����ɂȂ��Ă��邽�߁A
* �������傫�������菬���������肷��
*/
void NotesEditor::SlideNotes::DrawCurve()
{
	Engine::Components::Position position = *screenPos;
	float height = transform->GetSize().height * transform->GetSize().scaleHeight;

	for (size_t i = 0; i < dx_.size() - 1; i++)
	{
		// dx_[i] - dx_[0]
		DrawBoxAA(dy_[i] + 40, position.y + (dx_[i] - dx_[0] + height / 2) + 1,
			dy_[i + 1] - 40, position.y + (dx_[i + 1] - dx_[0] + height / 2) - 1, lineColor, true);
	}
}

void NotesEditor::SlideNotes::SetPoint()
{
	// �_�̍��W�i�[���X�g
	std::vector<vector<double>> p_;
	p_.resize(notesList.size());

	// ���ԓ_�̍��W����
	// y-x�̊֐��Ȃ̂�x��y���t�ɂ���
	for (int i = 0; i < notesList.size(); i++)
	{
		p_[i].push_back(notesList[i]->GetTransform().GetPosition().y);
		p_[i].push_back(notesList[i]->GetTransform().GetPosition().x);
	}

	//�X�v���C�����
	cubicSpline.cubicSpline(p_, p_.size());
	//�e�_�Ԃ̕�ԓ_��
	int splitNum;

	for (size_t i = 0; i < p_.size() - 1; i++)
	{
		// x���W�������Ȃ烊�\�[�X�팸�̂��߂ɕ�������1�ɂ���
		if (p_[i][1] == p_[i + 1][1])
			splitNum = 1;
		else
			// �������̒���
			splitNum = fabs(p_[i + 1][0] - p_[i][0]);

		// 2�_�Ԃ̋������ԓ_���Ŋ���
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
		// �X�v���C����Ԍ��ʏ�����
		cubicSpline.Init();
		// ��ԓ_���X�g��������
		dx_.clear();
		dx_.shrink_to_fit();
		dy_.clear();
		dy_.shrink_to_fit();
		SetPoint();
	}
}

