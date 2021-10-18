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

void NotesEditor::Bar::ChangedTransformByScale(float scaleHeight)
{
	float beforeHeight = transform->GetSize().height * transform->GetSize().scaleHeight;
	float afterHeight = transform->GetSize().height * scaleHeight;
	float diff = beforeHeight - afterHeight;

	float beforeScale = transform->GetSize().scaleHeight;

	// 座標とスケールの更新
	transform->SetPosition(transform->GetPosition().x,
		transform->GetPosition().y * (scaleHeight / beforeScale));
	transform->Scaling(1.f, scaleHeight);

	// １小節目の下端をウィンドウの下端に合わせる 
	transform->Translate(0.f, diff * (1.f / beforeScale));

	collider->Update();

	for (auto bar : barLineList)
		bar->ChangedPosByScale();
}

int NotesEditor::Bar::LineNum(float y)
{
	const int NONE = -1;
	for (size_t i = 0; i < barLineList.size(); i++)
	{
		if (barLineList[i]->GetTransform().GetPosition().y == y)
			return static_cast<int>(i);
	}
	return NONE;
}

bool NotesEditor::Bar::Collision(float x,float y)
{
	return collision->Collision(x, y, *collider);
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
	const float turningNum = 8.f;
	const float lineThickness = 2.f;
	float height = BARHEIGHT * transform->GetSize().scaleHeight;
	float barBottom = screenPos->y + height / 2.f;

	// 小節の縦範囲に合わせて黒色のボックス描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBoxAA(screenPos->x + BARWIDTH / 2.f - turningNum, screenPos->y + height / 2.f, WINDOW_SIZE_WIDTH, screenPos->y - height / 2.f + lineThickness, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawLineAA(screenPos->x + BARWIDTH / 2.f, screenPos->y + height / 2.f, WINDOW_SIZE_WIDTH, screenPos->y + height / 2.f, GetColor(255, 255, 255), lineThickness);
	DrawFormatStringFToHandle(screenPos->x + BARWIDTH / 4.f * 3.f - turningNum * 2.5f, screenPos->y, GetColor(255, 255, 255), fontHandle, "%d", barNum + 1);
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
