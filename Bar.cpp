#include "DxLib.h"
#include "WindowSize.hpp"
#include "Bar.hpp"
#include "BarManager.hpp"
#include <math.h>

//static変数の実体化
int Bar::fontHandle;

int Bar::lane[6];

Bar::Bar(int handle, int i) noexcept : barNum(i) {
	imageHandle = handle;
	GetGraphSize(handle, &width, &height);
	position.x = WINDOW_SIZE_WIDTH / 2;
	position.y = WINDOW_SIZE_HEIGHT / 2 - height * (WINDOW_SIZE_HEIGHT / height) * i;
	collisionPos.x = WINDOW_SIZE_WIDTH / 2;
	collisionPos.y = WINDOW_SIZE_HEIGHT / 2 - height * (WINDOW_SIZE_HEIGHT / height) * i;

	if (barNum == 0) {
		InitLaneArray();
	}
}

Bar::~Bar() noexcept {

}
void Bar::Update() noexcept {
}

void Bar::Draw() noexcept {
	DrawModiGraph(
		position.x - (float)width / 2, position.y - (float)height / 2, //左上座標
		position.x + (float)width / 2, position.y - (float)height / 2, //右上座標
		position.x + (float)width / 2, position.y + (float)height / 2, //右下座標
		position.x - (float)width / 2, position.y + (float)height / 2, //左下座標
		imageHandle, true); //グラフィックハンドル、透過処理
	DrawFormatStringToHandle(780, position.y + (float)height / 2 - 20, GetColor(255, 255, 255), fontHandle, "%d", barNum + 1);
	DebugDraw();
}

//当たり判定
void Bar::Collision() noexcept {
	int x, y;
	GetMousePoint(&x, &y);
	DrawFormatString(800, 400, GetColor(0, 255, 0), "当たり判定実行");
	if (CollisionBar(x, y)) {
		DrawFormatString(800, 450, GetColor(0, 255, 0), "%d小節目", barNum + 1);
		CollisionLane(x);
		CollisionLine(y);
	}
}

bool Bar::CollisionBar(int& x, int& y) noexcept {
	if (x >= position.x - width / 4 && x <= position.x + width / 4 &&
		y >= position.y - height / 2 && y <= position.y + height / 2) {
		return true;
	}
	return false;
}

//レーン判定
void Bar::CollisionLane(int& x) noexcept {
	//初期の最小値設定
	int min = abs(lane[0] - x);
	int laneIndex = 0;
	for (int i = 1; i < 6; i++) {
		if (min > abs(lane[i] - x)) {
			min = abs(lane[i] - x);
			laneIndex = i;
		}
	}
	//return lane[laneIndex];
}

//何分目なのかを判定
void Bar::CollisionLine(int& y) noexcept {
	std::vector<int> linePosYList;
	MakeLineCollisionList(linePosYList);
	int min = abs(linePosYList[0]);
	int lineIndex = 0;
	for (int i = 1; i < linePosYList.size(); i++) {
		if (min > abs(lane[i] - y)) {
			min = abs(lane[i] - y);
			lineIndex = i;
		}
	}
	//return lane[lineIndex];
}

void Bar::DebugDraw() noexcept {
	if (barNum == 3) {
		int x, y;
		GetMousePoint(&x, &y);
		unsigned int c = GetColor(0, 255, 0);
	}
	//DrawFormatString(800, 500, GetColor(0, 255, 0), "List1:%d", line1.size());
	//DrawFormatString(800, 525, GetColor(0, 255, 0), "List4:%d", line4.size());
	//DrawFormatString(800, 550, GetColor(0, 255, 0), "List8:%d", line8.size());
	//DrawFormatString(800, 575, GetColor(0, 255, 0), "List16:%d", line16.size());
	//DrawFormatString(800, 600, GetColor(0, 255, 0), "List32:%d", line32.size());
	//for (int i = 0; i < line16.size() / 2; i++) {
	//	DrawFormatString(800, 350 + 25 * (i + 1), GetColor(0, 255, 0), "posY%d:%d", 2 * i, line16[2 * i]);
	//	DrawFormatString(900, 350 + 25 * (i + 1), GetColor(0, 255, 0), "posY%d:%d", 2 * i + 1, line16[2 * i + 1]);
	//}
}

void Bar::MakeLineCollisionList(std::vector<int>& list) noexcept {
	switch (BarManager::GetBarType())
	{
	case BAR1:
		MakeList(list, 1);
		break;
	case BAR4:
		MakeList(list, 4);
		break;
	case BAR8:
		MakeList(list, 8);
		break;
	case BAR16:
		MakeList(list, 16);
		break;
	case BAR32:
		MakeList(list, 32);
		break;
	default:
		break;
	}
}

//リスト作成
void Bar::MakeList(std::vector<int>& list, int lineNum) noexcept {
	for (int i = 0; i < lineNum; i++) {
		list.push_back(height / lineNum * (i + 1));
	}
}

void Bar::InitLaneArray() noexcept {
	lane[0] = 307;
	lane[1] = 390;
	lane[2] = 472;
	lane[3] = 555;
	lane[4] = 637;
	lane[5] = 720;
}