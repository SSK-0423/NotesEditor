#include "Bar.hpp"
#include "WindowSize.hpp"
#include "DxLib.h"
#define ADD 20

BarController::BarController() {
}
BarController::~BarController() {
}

void BarController::SetObject(GameObject* bar) {
	bars.push_back(bar);
}

void BarController::SetHandle(int& handle) {
	barHandle.push_back(handle);
	DrawFormatString(800, 250, GetColor(0, 255, 0), "BarController関数");
}

void BarController::ChangeHandle() {
	DrawFormatString(800, 250, GetColor(0, 255, 0), "ChangeHandle関数");
	ChangeBarHandle(barHandle[0]);
}
void BarController::ChangeHandle4() {
	DrawFormatString(800, 250, GetColor(0, 255, 0), "ChangeHandle4関数");
	ChangeBarHandle(barHandle[1]);
}
void BarController::ChangeHandle8() {
	DrawFormatString(800, 250, GetColor(0, 255, 0), "ChangeHandle8関数");
	ChangeBarHandle(barHandle[2]);
}
void BarController::ChangeHandle16() {
	DrawFormatString(800, 250, GetColor(0, 255, 0), "ChangeHandle16関数");
	ChangeBarHandle(barHandle[3]);
}
void BarController::ChangeHandle32() {
	DrawFormatString(800, 250, GetColor(0, 255, 0), "ChangeHandle32関数");
	ChangeBarHandle(barHandle[4]);
}

void BarController::ChangeBarHandle(int handle) {
	for (auto i : bars) {
		i->SetHandle(handle);
	}
}

void BarController::Update() {
	if (CheckHitKey(KEY_INPUT_D) != 0) {
		DeleteObj();
	}
}
void BarController::Draw() {
	DrawFormatString(800,200,GetColor(0,255,0),"小節線数:%d",bars.size());
}
void BarController::DeleteObj() {
	bars.clear();
}

Bar::Bar(int handle, int i) {
	barNum = i;
	imageHandle = handle;
	GetGraphSize(handle, &width, &height);
	position.x = WINDOW_SIZE_WIDTH / 2;
	//position.y = WINDOW_SIZE_HEIGHT / 2 - WINDOW_SIZE_HEIGHT * i - ADD * i;
	position.y = WINDOW_SIZE_HEIGHT / 2 - height * i;
	collisionPos.x = WINDOW_SIZE_WIDTH / 2;
	//collisionPos.y = WINDOW_SIZE_HEIGHT / 2 - WINDOW_SIZE_HEIGHT * i - ADD * i;
	collisionPos.y = WINDOW_SIZE_HEIGHT / 2 - height * i;
	type = BAR32;
	//height = 1024;
}
Bar::~Bar() {

}
void Bar::Update() {
}
void Bar::Draw() {
	DrawModiGraph(
		position.x - width / 2, position.y - height / 2, //左上座標
		position.x + width / 2, position.y - height / 2, //右上座標
		position.x + width / 2, position.y + height / 2, //右下座標
		position.x - width / 2, position.y + height / 2, //左下座標
		imageHandle, true); //グラフィックハンドル、透過処理
}
void Bar::SetHandle(int handle) {
	imageHandle = handle;
}
