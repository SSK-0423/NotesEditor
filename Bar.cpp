#include "DxLib.h"
#include "WindowSize.hpp"
#include "Bar.hpp"

//static変数の実体家
int Bar::fontHandle;
std::vector<int> Bar::line1;
std::vector<int> Bar::line4;
std::vector<int> Bar::line8;
std::vector<int> Bar::line16;
std::vector<int> Bar::line32;

Bar::Bar(int handle, int i) noexcept : barNum(i) {
	imageHandle = handle;
	GetGraphSize(handle, &width, &height);
	position.x = WINDOW_SIZE_WIDTH / 2;
	position.y = WINDOW_SIZE_HEIGHT / 2 - height * (WINDOW_SIZE_HEIGHT / height) * i;
	collisionPos.x = WINDOW_SIZE_WIDTH / 2;
	collisionPos.y = WINDOW_SIZE_HEIGHT / 2 - height * (WINDOW_SIZE_HEIGHT / height) * i;

	if (barNum == 0) {
		MakeLineDistanceList();
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

void Bar::PutNotes() noexcept{
}


//当たり判定
void Bar::Collision() noexcept {
	int x, y;
	GetMousePoint(&x, &y);
	DrawFormatString(800, 400, GetColor(0, 255, 0), "当たり判定実行");
	if (x >= position.x - width / 4 && x <= position.x + width / 4 &&
		y >= position.y - height / 2 && y <= position.y + height / 2) {
		DrawFormatString(800, 450, GetColor(0, 255, 0), "%d小節目", barNum + 1);
		CollisionLine(x,y);
	}
}

//何分目なのかを判定
void Bar::CollisionLine(int& x, int& y) noexcept {
	int num = 3;
	if (num == 3) {
		for (int posY : line16) {
			if (x >= posY + 10 && y <= posY - 10) {
				DrawBox(width / 2 - 10, posY - 10, width / 2 + 10, posY + 10, GetColor(0, 0, 255), true);
			}
		}
	}
}
void Bar::CollisionLane(int& x, int& y) noexcept {

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

void Bar::MakeLineDistanceList() noexcept {
	MakeList(line1, 1);
	MakeList(line4, 4);
	MakeList(line8, 8);
	MakeList(line16, 16);
	MakeList(line32, 32);
}

void Bar::MakeList(std::vector<int>& list, int lineNum) noexcept {
	for (int i = 0; i < lineNum; i++) {
		list.push_back(height / lineNum * (i + 1));
	}
}