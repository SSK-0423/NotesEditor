#include "DxLib.h"
#include "WindowSize.hpp"
#include "Bar.hpp"
#include "BarManager.hpp"
#include "Transform.hpp"
#include "Texture.hpp"
#include "BoxCollider.hpp"
#include "PointWithPolygon.hpp"
#include "BarLine.hpp"
#include <math.h>

NotesEditor::BARTYPE NotesEditor::Bar::nowType = NotesEditor::BARTYPE::BAR1;
const float NotesEditor::Bar::BARWIDTH = static_cast<float>(WINDOW_SIZE_WIDTH) / 2.f;
const float NotesEditor::Bar::BARHEIGHT = static_cast<float>(WINDOW_SIZE_HEIGHT);
Font NotesEditor::Bar::fontHandle;
int NotesEditor::Bar::MAXNOTENUM = 1;

NotesEditor::Bar::Bar(int barNum, int lineNum) : barNum(barNum)
{
	BarLine::stepPosY = BARHEIGHT / MAXNOTENUM;
	collider = new Engine::Components::BoxCollider(*transform);
	collision = new Engine::Collision::PointWithPolygon();
	// サイズ初期化
	transform->SetSize(BARWIDTH, BARHEIGHT);
	// 座標初期化
	InitPos(barNum);
	// 小節線の生成
	CreateBarLine(lineNum);
	collider->Update();
}

NotesEditor::Bar::~Bar()
{
	for (auto& line : barLineList)
	{
		delete line;
	}
	barLineList.clear();
	barLineList.shrink_to_fit();
	delete collider;
	delete collision;
}

void NotesEditor::Bar::Update()
{
	UpdateBarLine();
}

void NotesEditor::Bar::Draw()
{
	DrawBarLine();
	DrawBarNum();
}

float NotesEditor::Bar::DecidePutPosY(float x, float y)
{
	const float NONE = -1.f;
	if (!IsOnBar(x, y)) return NONE;
	float putPoxY;
	for (size_t i = 0; i < barLineList.size(); i += static_cast<int>(nowType))
	{
		putPoxY = barLineList[i]->DecidePutPosY(x, y);
		if (putPoxY != -1.f) return putPoxY;
	}
	return NONE;
}

void NotesEditor::Bar::ChangeBarType(BARTYPE type)
{
	nowType = type;
}

void NotesEditor::Bar::InitPos(int barNum)
{
	/*
	* 座標
	* X:ウィンドウの中央
	* Y:ウィンドウの中央 - 小節番号 * 小節の高さ
	*/
	transform->SetPosition(static_cast<float>(WINDOW_SIZE_WIDTH) / 2.f, static_cast<float>(WINDOW_SIZE_HEIGHT) / 2.f - BARHEIGHT * barNum);
	screenPos->SetPosition(static_cast<float>(WINDOW_SIZE_WIDTH) / 2.f, static_cast<float>(WINDOW_SIZE_HEIGHT) / 2.f - BARHEIGHT * barNum);
}

void NotesEditor::Bar::CreateBarLine(int lineNum)
{
	for (int i = 0; i < lineNum; i++)
	{
		barLineList.push_back(new BarLine(*this, i));
	}
}

void NotesEditor::Bar::UpdateBarLine()
{
	for (size_t i = 0; i < barLineList.size(); i += static_cast<int>(nowType))
	{
		barLineList[i]->Update();
	}
}

void NotesEditor::Bar::DrawBarNum()
{
	DrawFormatStringToHandle(780, screenPos->y + static_cast<float>(transform->GetSize().height) / 2.f - 20.f, GetColor(255, 255, 255), fontHandle, "%d", barNum + 1);
}

void NotesEditor::Bar::DrawBarLine()
{
	for (size_t i = 0; i < barLineList.size(); i += static_cast<int>(nowType))
	{
		barLineList[i]->Draw();
	}
}

bool NotesEditor::Bar::IsOnBar(float x, float y)
{
	return collision->Collision(x, y, *collider);
}
