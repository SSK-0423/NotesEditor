#include "BarLine.hpp"
#include "Transform.hpp"
#include "BoxCollider.hpp"
#include "PointWithPolygon.hpp"
#include "WindowSize.hpp"
#include "InputDeviceContainer.hpp"
#include "Point.hpp"

//static�ϐ����̉�
Color NotesEditor::BarLine::lineColor[4] = {
	GetColor(255,255,255),	//��
	GetColor(0,255,255),	//���F
	GetColor(255,255,0),	//���F
	GetColor(255,0,255)		//�s���N
};

int NotesEditor::BarLine::lineThickness = 2;

float NotesEditor::BarLine::stepPosY;

void NotesEditor::BarLine::InitTransform()
{
	float windowWidth = static_cast<float>(WINDOW_SIZE_WIDTH);
	float windowHeight = static_cast<float>(WINDOW_SIZE_HEIGHT);

	float width = windowWidth / 2.f;
	float height = 20.f;

	float x = parentBar.GetTransform().GetPosition().x;
	float y = parentBar.GetTransform().GetPosition().y +
		windowHeight / 2.f - stepPosY * static_cast<float>(lineNum);

	// ���C���̎n�_�I�_������
	startPoint->x = windowWidth / 4.f;
	startPoint->y = y;
	endPoint->x = windowWidth - windowWidth / 4.f;
	endPoint->y = y;

	// transform������
	transform->SetPosition(x, y);
	transform->SetSize(width, height);

	// collider��transform�̃p�����[�^����
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
	delete transform;
	delete collider;
	delete collision;
	delete startPoint;
	delete endPoint;
}

void NotesEditor::BarLine::Update()
{
	float y = parentBar.GetScreenPos().y + static_cast<float>(WINDOW_SIZE_HEIGHT) / 2.f - stepPosY * lineNum;
	startPoint->y = y;
	endPoint->y = y;
}

void NotesEditor::BarLine::Draw()
{
	DrawLineAA(startPoint->x, startPoint->y, endPoint->x, endPoint->y, color, lineThickness);
}

float NotesEditor::BarLine::Collision(float x, float y)
{
	if (collision->Collision(x, y, *collider))
	{
		/* ���� */
		DrawFormatString(700, 75, GetColor(0, 255, 0), "��������:%d", lineNum);
		return transform->GetPosition().y;
	}
	return -1.f;
}
