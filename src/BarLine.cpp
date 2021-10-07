#include "BarLine.hpp"
#include "Transform.hpp"
#include "BoxCollider.hpp"
#include "PointWithPolygon.hpp"
#include "WindowSize.hpp"
#include "InputDeviceContainer.hpp"

//static�ϐ����̉�
Color NotesEditor::BarLine::lineColor[4] = {
	GetColor(255,255,255),	//��
	GetColor(0,255,255),	//���F
	GetColor(255,255,0),	//���F
	GetColor(255,0,255)		//�s���N
};	

int NotesEditor::BarLine::lineThickness = 2;

void NotesEditor::BarLine::InitTransform()
{
	float step = WINDOW_SIZE_HEIGHT / 32.f;

	float width = WINDOW_SIZE_WIDTH / 2.f;
	float height = 10.f;

	float x = parentBar.GetTransform().GetPosition().x;
	float y = parentBar.GetTransform().GetPosition().y + WINDOW_SIZE_HEIGHT / 2.f;

	transform->SetPosition(x, y - step * static_cast<float>(lineNum));
	transform->SetSize(width, height);
	transform->Scaling(1, 1);
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
	InitTransform();
	InitColor();
}

NotesEditor::BarLine::~BarLine()
{
	delete transform;
	delete collider;
	delete collision;
}

void NotesEditor::BarLine::Update()
{
}

void NotesEditor::BarLine::Draw()
{
	float step = WINDOW_SIZE_HEIGHT / 32.f;
	float sx = WINDOW_SIZE_WIDTH / 4.f;
	float ex = WINDOW_SIZE_WIDTH - WINDOW_SIZE_WIDTH / 4.f;
	float sy = parentBar.GetScreenPos().y + WINDOW_SIZE_HEIGHT / 2.f;
	DrawLine(sx, sy - step * lineNum, ex, sy - step * lineNum, color, lineThickness);
}

void NotesEditor::BarLine::Collision(float x, float y)
{
	if (collision->Collision(x, y, *collider))
	{
		/* ���� */
		DrawFormatString(700, 75, GetColor(0, 255, 0), "��������:%d",lineNum);
	}
}
