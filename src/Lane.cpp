#include "Lane.hpp"
#include "WindowSize.hpp"
#include "Transform.hpp"
#include "BoxCollider.hpp"
#include "PointWithPolygon.hpp"
#include "Point.hpp"

int NotesEditor::Lane::MAXLANENUM = 6;
int NotesEditor::Lane::lineThickness = 2;
Color NotesEditor::Lane::laneColor = GetColor(255, 255, 255);
float NotesEditor::Lane::stepPosX = (static_cast<float>(WINDOW_SIZE_WIDTH) / 2.f) / static_cast<float>(MAXLANENUM);

NotesEditor::Lane::Lane(int laneNum, float posX) : laneNum(laneNum)
{
	collider = new Engine::Components::BoxCollider(*transform);
	collision = new Engine::Collision::PointWithPolygon();
	startPoint = new Engine::PrimitiveObj::Point();
	endPoint = new Engine::PrimitiveObj::Point();

	float windowWidth = static_cast<float>(WINDOW_SIZE_WIDTH);
	float windowHeight = static_cast<float>(WINDOW_SIZE_HEIGHT);

	float width = 10.f;
	float height = windowHeight;

	float x = posX;
	float y = windowHeight / 2.f;

	// ���C���̎n�_�I�_������
	startPoint->x = x;
	startPoint->y = 0.f;
	endPoint->x = x;
	endPoint->y = windowHeight;

	// transform������
	transform->SetPosition(x, y);
	transform->SetSize(width, height);

	// collider��transform�̃p�����[�^����
	collider->Update();
}

NotesEditor::Lane::~Lane()
{
	delete collider;
	delete collision;
	delete startPoint;
	delete endPoint;
}

void NotesEditor::Lane::Update()
{
}

void NotesEditor::Lane::Draw()
{
	DrawLineAA(startPoint->x, startPoint->y, endPoint->x, endPoint->y, laneColor, lineThickness);
}

void NotesEditor::Lane::Collision(float x, float y)
{
	if (collision->Collision(x, y, *collider))
		DrawFormatString(700, 200, GetColor(0, 255, 0), "��������:���[��%d", laneNum + 1);
}
