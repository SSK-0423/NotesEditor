//#include "DxLib.h"
//#include "WindowSize.hpp"
//#include "Bar.hpp"
//#include "BarManager.hpp"
//#include <math.h>
//
////static変数の実体化
//int Bar::fontHandle;
//
//int Bar::lane[6];
//
//Bar::Bar(int handle, int i) noexcept : barNum(i) {
//	imageHandle = handle;
//	GetGraphSize(handle, &width, &height);
//	position.x = WINDOW_SIZE_WIDTH / 2;
//	position.y = WINDOW_SIZE_HEIGHT / 2 - height * (WINDOW_SIZE_HEIGHT / height) * i;
//	collisionPos.x = WINDOW_SIZE_WIDTH / 2;
//	collisionPos.y = WINDOW_SIZE_HEIGHT / 2 - height * (WINDOW_SIZE_HEIGHT / height) * i;
//
//	if (barNum == 0) {
//		InitLaneArray();
//	}
//}
//
//Bar::~Bar() noexcept {
//
//}
//
//void Bar::Update() noexcept {
//}
//
//void Bar::Draw() noexcept {
//	DrawModiGraph(
//		position.x - (float)width / 2, position.y - (float)height / 2, //左上座標
//		position.x + (float)width / 2, position.y - (float)height / 2, //右上座標
//		position.x + (float)width / 2, position.y + (float)height / 2, //右下座標
//		position.x - (float)width / 2, position.y + (float)height / 2, //左下座標
//		imageHandle, true); //グラフィックハンドル、透過処理
//	DrawFormatStringToHandle(780, position.y + (float)height / 2 - 20, GetColor(255, 255, 255), fontHandle, "%d", barNum + 1);
//	DebugDraw();
//}
//
////当たり判定
//void Bar::Collision(float& posX, float& posY) noexcept {
//	int x, y;
//	GetMousePoint(&x, &y);
//	//DrawFormatString(800, 400, GetColor(0, 255, 0), "当たり判定実行");
//	if (CollisionBar(x, y)) {
//		//DrawFormatString(800, 450, GetColor(0, 255, 0), "%d小節目", barNum + 1);
//		posX = CollisionLane(x);
//		posY = CollisionLine(y);
//	}
//}
//
//bool Bar::CollisionBar(int& x, int& y) noexcept {
//	if (x >= position.x - width / 4 && x <= position.x + width / 4 &&
//		y >= position.y - height / 2 && y <= position.y + height / 2) {
//		return true;
//	}
//	return false;
//}
//
////レーン判定
//float Bar::CollisionLane(int& x) noexcept {
//	//初期の最小値設定
//	int min = abs(lane[0] - x);
//	int laneIndex = 0;
//	for (int i = 1; i < 6; i++) {
//		if (min > abs(lane[i] - x)) {
//			min = abs(lane[i] - x);
//			laneIndex = i;
//		}
//	}
//	return lane[laneIndex];
//}
//
////何分目なのかを判定
//float Bar::CollisionLine(int& y) noexcept {
//
//	//小節線の開始位置からの距離
//	std::vector<int> linePosYList;
//	MakeLineCollisionList(linePosYList);
//
//	//描画座標を使って判定
//	float startBarPosY = this->position.y + height / 2;
//	//初期の最小距離
//	int min = abs(startBarPosY - y);
//	//初期インデックス
//	int lineIndex = 0;
//	//判定処理
//	for (int i = 1; i < linePosYList.size(); i++) {
//		if (min > abs(startBarPosY - linePosYList[i] - y)) {
//			min = abs(startBarPosY - linePosYList[i] - y);
//			lineIndex = i;
//		}
//	}
//	//小節線からの相対座標から絶対座標に変換
//	float posY = this->collisionPos.y + height / 2 - linePosYList[lineIndex];
//	return posY;
//}
//
//void Bar::DebugDraw() noexcept {
//	if (barNum == 3) {
//		int x, y;
//		GetMousePoint(&x, &y);
//		unsigned int c = GetColor(0, 255, 0);
//	}
//}
//
//void Bar::MakeLineCollisionList(std::vector<int>& list) noexcept {
//	switch (BarManager::GetBarType())
//	{
//	case BAR1:
//		MakeList(list, 1);
//		break;
//	case BAR4:
//		MakeList(list, 4);
//		break;
//	case BAR8:
//		MakeList(list, 8);
//		break;
//	case BAR16:
//		MakeList(list, 16);
//		break;
//	case BAR32:
//		MakeList(list, 32);
//		break;
//	default:
//		break;
//	}
//}
//
////リスト作成
//void Bar::MakeList(std::vector<int>& list, int lineNum) noexcept {
//	//小節線の開始位置との判定に必要
//	list.push_back(0);
//	for (int i = 0; i < lineNum; i++) {
//		list.push_back(height / lineNum * (i + 1));
//	}
//}
//
//void Bar::InitLaneArray() noexcept {
//	lane[0] = 307;
//	lane[1] = 390;
//	lane[2] = 472;
//	lane[3] = 555;
//	lane[4] = 637;
//	lane[5] = 720;
//}