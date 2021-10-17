#include "BarLine.hpp"
#include "Transform.hpp"
#include "BoxCollider.hpp"
#include "PointWithPolygon.hpp"
#include "WindowSize.hpp"
#include "InputDeviceContainer.hpp"
#include "Point.hpp"
#include "DxLib.h"

//static�ϐ����̉�
Color NotesEditor::BarLine::lineColor[4] = {
	GetColor(255,255,255),	//��
	GetColor(0,255,255),	//���F
	GetColor(255,255,0),	//���F
	GetColor(255,0,255)		//�s���N
};

int NotesEditor::BarLine::lineThickness = 2;
float NotesEditor::BarLine::stepPosY;
const float NotesEditor::BarLine::BARLINEWIDTH = static_cast<float>(WINDOW_SIZE_WIDTH) / 2.f;
const float NotesEditor::BarLine::BARLINEHEIGHT = 20.f;

NotesEditor::BarLine::BarLine(const Engine::GameObject& parentBar, int lineNum) : parentBar(parentBar), lineNum(lineNum)
{
	collider = new Engine::Components::BoxCollider(*transform);
	collision = new Engine::Collision::PointWithPolygon();
	startPoint = new Engine::PrimitiveObj::Point();
	endPoint = new Engine::PrimitiveObj::Point();
	InitTransform();
	InitColor();
}

NotesEditor::BarLine::~BarLine()
{
	delete collider;
	delete collision;
	delete startPoint;
	delete endPoint;
}

void NotesEditor::BarLine::Update()
{
	UpdateScreenPos();
	collider->Update();
}

void NotesEditor::BarLine::Draw()
{
	DrawLineAA(startPoint->x, startPoint->y, endPoint->x, endPoint->y, color, lineThickness);
	DrawFormatString(endPoint->x, endPoint->y, color, "Y:%5.0f", endPoint->y);
	//DrawFormatString(endPoint->x + 100.f, endPoint->y + 12.5f, color, "BY:%5.0f", beforePos);
	DrawFormatString(endPoint->x + 100.f, endPoint->y + 12.5f, color, "diff:%5.0f", endPoint->y - beforePos);
}

void NotesEditor::BarLine::OnChangedScale()
{
	beforePos = endPoint->y;
	UpdatePosition();
}

float NotesEditor::BarLine::DecidePutPosY(float x, float y)
{
	const float NONE = -1.f;
	if (collision->Collision(x, y, *collider))
		return transform->GetPosition().y;
	return NONE;
}

float NotesEditor::BarLine::CalcScreenPos()
{
	// ���߂̉��[���W = ���߂̒��S���W + ���߂̃T�C�Y / 2;
	float barHeight = parentBar.GetTransform().GetSize().height * parentBar.GetTransform().GetSize().scaleHeight;
	// ���߂̉��[���W + ���̒P��y���W * ���ԍ� 
	float barBottomPos = parentBar.GetScreenPos().y + barHeight / 2.f;
	// ���߂̍����X�P�[��
	float barScale = parentBar.GetTransform().GetSize().scaleHeight;
	return barBottomPos - stepPosY * barScale * lineNum;
}

void NotesEditor::BarLine::UpdateScreenPos()
{
	float y = CalcScreenPos();
	startPoint->y = y;
	endPoint->y = y;
}

void NotesEditor::BarLine::UpdatePosition()
{
	// ���߂̉��[���W = ���߂̒��S���W + ���߂̃T�C�Y / 2;
	float barHeight = parentBar.GetTransform().GetSize().height * parentBar.GetTransform().GetSize().scaleHeight;
	// ���߂̉��[���W + ���̒P��y���W * ���ԍ� 
	float barBottomPos = parentBar.GetTransform().GetPosition().y + barHeight / 2.f;
	// ���߂̍����X�P�[��
	float barScale = parentBar.GetTransform().GetSize().scaleHeight;
	transform->SetPosition(transform->GetPosition().x, barBottomPos - stepPosY * barScale * lineNum);
}

void NotesEditor::BarLine::InitTransform()
{
	float windowWidth = static_cast<float>(WINDOW_SIZE_WIDTH);
	float windowHeight = static_cast<float>(WINDOW_SIZE_HEIGHT);

	float x = parentBar.GetTransform().GetPosition().x;
	float y = parentBar.GetTransform().GetPosition().y +
		parentBar.GetTransform().GetSize().height / 2.f - stepPosY * static_cast<float>(lineNum) * parentBar.GetTransform().GetSize().scaleHeight;

	// ���C���̎n�_�I�_������
	startPoint->x = windowWidth / 4.f;
	startPoint->y = y;
	endPoint->x = windowWidth - windowWidth / 4.f;
	endPoint->y = y;

	transform->SetPosition(x, y);
	transform->SetSize(BARLINEWIDTH, BARLINEHEIGHT);
	collider->Update();
}

void NotesEditor::BarLine::InitColor()
{
	// ���F1/1, 1/4
	if (lineNum % 8 == 0)
		color = lineColor[0];
	// ���F�F1/8
	else if (lineNum % 4 == 0)
		color = lineColor[1];
	// ���F�F1/16
	else if (lineNum % 2 == 0)
		color = lineColor[2];
	// ���F1/32
	else if (lineNum % 2 == 1)
		color = lineColor[3];
}