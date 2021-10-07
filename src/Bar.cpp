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

//static変数の実体化
Font NotesEditor::Bar::fontHandle;
NotesEditor::BARTYPE NotesEditor::Bar::nowType = NotesEditor::BARTYPE::BAR1;
const int NotesEditor::Bar::MAXNOTENUM = 32;

//int NotesEditor::Bar::lane[6];

NotesEditor::Bar::Bar(int barNum) : barNum(barNum)
{
	collider = new Engine::Components::BoxCollider(*transform);
	collision = new Engine::Collision::PointWithPolygon();

	// サイズ初期化
	float width = static_cast<float>(WINDOW_SIZE_WIDTH) / 2.f;
	float height = static_cast<float>(WINDOW_SIZE_HEIGHT);

	transform->SetSize(width, height);

	// 座標初期化
	transform->SetPosition(static_cast<float>(WINDOW_SIZE_WIDTH) / 2.f,
		static_cast<float>(WINDOW_SIZE_HEIGHT) / 2.f - height * (static_cast<float>(WINDOW_SIZE_HEIGHT) / height) * barNum);
	screenPos->SetPosition(static_cast<float>(WINDOW_SIZE_WIDTH) / 2.f,
		static_cast<float>(WINDOW_SIZE_HEIGHT) / 2.f - height * (static_cast<float>(WINDOW_SIZE_HEIGHT) / height) * barNum);

	// 小節線の生成
	for (int i = 0; i < MAXNOTENUM; i++)
	{
		barLineList.push_back(new BarLine(*this, i));
	}
}

NotesEditor::Bar::~Bar()
{
	delete collider;
	delete collision;
}

void NotesEditor::Bar::Update()
{
	for (size_t i = 0; i < barLineList.size(); i += static_cast<int>(nowType))
	{
		barLineList[i]->Update();
	}
}

void NotesEditor::Bar::Draw()
{
	for (size_t i = 0; i < barLineList.size(); i += static_cast<int>(nowType))
	{
		barLineList[i]->Draw();
	}
}

void NotesEditor::Bar::Collision(float& x, float& y)
{
	bool isOnBar = collision->Collision(x, y, *collider);
	if (isOnBar)
	{
		for (auto line : barLineList)
		{
			line->Collision(x,y);
		}
		return;
	}
	return;
}

void NotesEditor::Bar::ChangeBarType(BARTYPE type)
{
	nowType = type;
}

void NotesEditor::Bar::DrawBarNum()
{
	// 小節線描画	
	DrawFormatStringToHandle(780, screenPos->y + static_cast<float>(transform->GetSize().height) / 2.f - 20.f, GetColor(255, 255, 255), fontHandle, "%d", barNum + 1);
}

void NotesEditor::Bar::DrawBarLine()
{
	for (auto line : barLineList)
	{
		line->Draw();
	}
}

//void NotesEditor::Bar::InitLaneArray() {
//	lane[0] = 307;
//	lane[1] = 390;
//	lane[2] = 472;
//	lane[3] = 555;
//	lane[4] = 637;
//	lane[5] = 720;
//}