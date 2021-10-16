#include "Lane.hpp"
#include "WindowSize.hpp"
#include "Transform.hpp"
#include "BoxCollider.hpp"
#include "PointWithPolygon.hpp"
#include "Point.hpp"
#include "GameUtility.hpp"
#include "DxLib.h"

int NotesEditor::Lane::lineThickness = 2;
Color NotesEditor::Lane::laneColor[2] = {
	GetColor(255, 255, 255),
	GetColor(0, 255, 255)
};

NotesEditor::Lane::Lane(int laneNum, float posX) : laneNum(laneNum), color(laneColor[laneNum % 2])
{
	startPoint = new Engine::PrimitiveObj::Point();
	endPoint = new Engine::PrimitiveObj::Point();

	float windowWidth = static_cast<float>(WINDOW_SIZE_WIDTH);
	float windowHeight = static_cast<float>(WINDOW_SIZE_HEIGHT);

	float width = 20.f;
	float height = windowHeight;

	float x = posX;
	float y = windowHeight / 2.f;

	// ラインの始点終点初期化
	startPoint->x = x;
	startPoint->y = 0.f;
	endPoint->x = x;
	endPoint->y = windowHeight;

	// transform初期化
	transform->SetPosition(x, y);
	transform->SetSize(width, height);

}

NotesEditor::Lane::~Lane()
{
	delete startPoint;
	delete endPoint;
}

void NotesEditor::Lane::Update()
{
}

void NotesEditor::Lane::Draw()
{
	DrawLineAA(startPoint->x, startPoint->y, endPoint->x, endPoint->y, color, lineThickness);
}
