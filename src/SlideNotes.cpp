#include "SlideNotes.hpp"
#include "Transform.hpp"
#include "BoxCollider.hpp"
#include "PointWithPolygon.hpp"
#include "DxLib.h"
#include <math.h>

#define DRAWMODE 1;
const float INF = 2000000.f;

//SlideNotes::SlideNotes(std::vector<ShortNotes*> list)  
//{
//	notesList = list;
//	Init();
//}
//
//SlideNotes::~SlideNotes()  
//{
//	for (auto obj : notesList) 
//	{
//		delete[] obj;
//	}
//	notesList.clear();
//}
//
//void SlideNotes::Init() 
//{
//	timing = 0;
//	width = CalcWidth();
//	height = fabs(notesList.back()->collisionPos.y - notesList[0]->collisionPos.y);
//	position.x = CalcColPosX();
//	collisionPos.x = CalcColPosX();
//	position.y = (notesList[0]->collisionPos.y + notesList.back()->collisionPos.y) / 2;
//	collisionPos.y = (notesList[0]->collisionPos.y + notesList.back()->collisionPos.y) / 2;
//	SetPoint();
//}
//
//void SlideNotes::Update()  
//{
//	for (auto notes : notesList) 
//	{
//		notes->SetPosition(position.x, position.y);
//	}
//}
//
//void SlideNotes::Draw()  
//{
//	DrawCurve();
//	DrawStartEnd();
//	DebugDraw();
//}
//
//void SlideNotes::SetNotesList(std::vector<ShortNotes*> list) 
//{
//	std::copy(list.begin(), list.end(), notesList.begin());
//
//	SetPoint();
//}
//
//
//void SlideNotes::SetPoint()  
//{
//	// �_�̍��W�i�[���X�g
//	std::vector<vector<double>> p_;
//	p_.resize(notesList.size());
//	// �F
//	Color color = GetColor(0, 0, 255);
//
//	// ���ԓ_�̍��W����
//	// y-x�̊֐��Ȃ̂�x��y���t�ɂ���
//	for (int i = 0; i < notesList.size(); i++) 
//	{
//		p_[i].push_back(notesList[i]->collisionPos.y);
//		p_[i].push_back(notesList[i]->collisionPos.x);
//	}
//
//	//�X�v���C�����
//	cubicSpline.cubicSpline(p_, p_.size());
//	//�e�_�Ԃ̕�ԓ_��
//	int splitNum = 100;
//
//	for (int i = 0; i < p_.size() - 1; i++)
//	{
//		// �������̒���
//		splitNum = fabs(p_[i + 1][0] - p_[i][0]) / 96 * 100;
//		// 2�_�Ԃ̋������ԓ_���Ŋ���
//		float step = fabs(p_[i + 1][0] - p_[i][0]) / splitNum;
//		SetInterpolationPoint(p_,step,splitNum,i);
//	}
//}
//
//// width�v�Z
//int SlideNotes::CalcWidth()  
//{
//	int max = GetMaxColPosX();
//	int min = GetMinColPosX();
//	if (max == min)
//		return ShortNotes::SHORTNOTESWIDTH;
//	return abs(max - min);
//}
//
//// CollisionPosX�����߂�
//int SlideNotes::CalcColPosX()  
//{
//	int max = GetMaxColPosX();
//	int min = GetMinColPosX();
//	return (max + min) / 2;
//}
//
//// CollisionPos�̍ő�l�擾
//int SlideNotes::GetMaxColPosX()
//{
//	int max = -INF;
//	for (auto notes : notesList) 
//	{
//		//�ő�l
//		if (notes->collisionPos.x > max)
//			max = notes->collisionPos.x;
//	}
//	return max;
//}
//
//// CollsionPos�̍ŏ��l�擾
//int SlideNotes::GetMinColPosX()
//{
//	int min = INF;
//	for (auto notes : notesList) 
//	{
//		//�ŏ��l
//		if (notes->collisionPos.x < min)
//			min = notes->collisionPos.x;
//	}
//	return min;
//}
//
//// ��ԓ_�Z�b�g
//void SlideNotes::SetInterpolationPoint(std::vector<vector<double>>& p_, float step, int splitNum, int i)
//{
//	for (int j = 0; j < splitNum + 1; j++) 
//	{
//		Vector2<float> vec = CalcInterpolationPoint(p_, step, splitNum, i, j);
//		// x���W(y���W)���
//		dx_.push_back(vec.y);
//		// y���W(x���W)���Ԋ֐���p���Čv�Z
//		dy_.push_back(vec.x);
//	}
//	// CalcInterpolationPoint(p_,step,splitNum,i);
//}
//
//// ��ԓ_�v�Z
//Vector2<float> SlideNotes::CalcInterpolationPoint(std::vector<vector<double>>& p_, float step, int splitNum, int i, int j)
//{
//	float x = cubicSpline.interpolation(p_[i][0] - step * (float)j, true);
//	float y = p_[i][0] - step * (float)j;
//	Vector2<float> vec;
//	vec.x = x;
//	vec.y = y;
//	return vec;
//}
//
//// x-y��y-x�ɕϊ������̂ŁAdx_ = dy_ dy = dx_
//void SlideNotes::DrawCurve()
//{
//	Color slideColor = GetColor(255, 255, 0);
//	for (int i = 1; i < dx_.size() - 1; i++) 
//	{
//		DrawBoxAA(dy_[i] + 40, position.y + (dx_[i] - dx_[0] + height / 2) + 1,
//			dy_[i] - 40, position.y + (dx_[i] - dx_[0] + height / 2) - 1, slideColor, true);
//	}
//}
//
//// �n�_�ƏI�_�̕`��
//void SlideNotes::DrawStartEnd()
//{
//	Color StartEndColor = GetColor(255, 192, 0);
//	//�n�_�ƏI�_
//	DrawBoxAA(dy_[0] - 40, position.y + height / 2 - 5,
//			dy_[0] + 40, position.y + height / 2 + 5, StartEndColor, true);
//	DrawBoxAA(dy_.back() - 40, (position.y - height / 2) - 5,
//			dy_.back() + 40, (position.y - height / 2) + 5, StartEndColor, true);
//
//}
//
//// �f�o�b�O�p�`��
//void SlideNotes::DebugDraw()
//{
//	int x;
//	int y;
//
//	GetMousePoint(&x, &y);
//
//	//DrawFormatString(800, 500, GetColor(0, 255, 0), "ColPosY:%f", this->collisionPos.y);
//	//DrawFormatString(800, 525, GetColor(0, 255, 0), "positionY:%f", position.y);// + dx_[0] + 5);
//	//DrawFormatString(800, 550, GetColor(0, 255, 0), "MouseX:%d,MouseY:%d", x, y);// + dx_[0] + 5);
//	//DrawFormatString(800, 575, GetColor(0, 255, 0), "width:%d", width);// + dx_[0] + 5);
//	//DrawFormatString(800, 600, GetColor(0, 255, 0), "height:%d", height);// + dx_[0] + 5);
//
//	DrawBox(position.x - width / 2, position.y - height / 2, position.x + width / 2, position.y + height / 2, GetColor(255, 0, 0), false);
//	DrawCircle(position.x, position.y, 10, GetColor(255, 255, 255), true);
//}

NotesEditor::SlideNotes::SlideNotes(std::vector<ShortNotes*> list)
{
	notesList = list;

	collider = new Engine::Components::BoxCollider(*transform);
	collision = new Engine::Collision::PointWithPolygon();

	float width = CalcWidth();
	float height = CalcHeight();
	float x = (GetMaxPosX() + GetMinPosX()) / 2.f;
	float y = (notesList[0]->GetTransform().GetPosition().y + notesList.back()->GetTransform().GetPosition().y) / 2.f;

	transform->SetPosition(x, y);
	transform->SetSize(width, height);

	collider->Update();
	SetPoint();
}

NotesEditor::SlideNotes::~SlideNotes()
{
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
	//�n�_�ƏI�_
	//DrawBoxAA(dy_[0] - 40, position.y + height / 2 - 5,
	//	dy_[0] + 40, position.y + height / 2 + 5, StartEndColor, true);
	//DrawBoxAA(dy_.back() - 40, (position.y - height / 2) - 5,
	//	dy_.back() + 40, (position.y - height / 2) + 5, StartEndColor, true);

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
	// �_�̍��W�i�[���X�g
	std::vector<vector<double>> p_;
	p_.resize(notesList.size());
	// �F
	Color color = GetColor(0, 0, 255);

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

	for (int i = 0; i < p_.size() - 1; i++)
	{
		//// x���W�������Ȃ烊�\�[�X�팸�̂��߂ɕ�������1�ɂ���
		if (p_[i][1] == p_[i + 1][1])
		{
			splitNum = 1;
		}
		else
		{
			// �������̒���
			splitNum = fabs(p_[i + 1][0] - p_[i][0]);
		}
		// �������̒���
		//splitNum = fabs(p_[i + 1][0] - p_[i][0]) / 96 * 96;
		// 2�_�Ԃ̋������ԓ_���Ŋ���
		float step = fabs(p_[i + 1][0] - p_[i][0]) / splitNum;
		SetInterpolationPoint(p_, step, splitNum, i);
	}
}

void NotesEditor::SlideNotes::Init()
{
}

