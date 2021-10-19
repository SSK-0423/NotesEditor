#include "Lane.hpp"
#include "WindowSize.hpp"
#include "Transform.hpp"
#include "BoxCollider.hpp"
#include "PointWithPolygon.hpp"
#include "Point.hpp"
#include "GameUtility.hpp"
#include "DxLib.h"

int NotesEditor::Lane::lineThickness = 1;
Color NotesEditor::Lane::laneColor[2] = {
	GetColor(255, 255, 255),
	GetColor(0, 255, 255)
};
const float NotesEditor::Lane::LANEWIDTH = 20.f;
const float NotesEditor::Lane::LANEHEIGHT = static_cast<float>(WINDOW_SIZE_HEIGHT);

NotesEditor::Lane::Lane(int laneNum, float posX) : laneNum(laneNum), color(laneColor[laneNum % 2])
{
	startPoint = new Engine::PrimitiveObj::Point();
	endPoint = new Engine::PrimitiveObj::Point();
	
	float x = posX;
	float y = LANEHEIGHT / 2.f;
	
	// ���C���̎n�_�I�_������
	startPoint->x = x;
	startPoint->y = 0.f;
	endPoint->x = x;
	endPoint->y = LANEHEIGHT;
	
	// transform������
	transform->SetPosition(x, y);
	transform->SetSize(LANEWIDTH, LANEHEIGHT);
}

NotesEditor::Lane::~Lane()
{
	delete startPoint;
	delete endPoint;
}

void NotesEditor::Lane::Update()
{
	// �������Ȃ�
}

void NotesEditor::Lane::Draw()
{
	DrawLineAA(startPoint->x, startPoint->y, endPoint->x, endPoint->y, color, lineThickness);
}
