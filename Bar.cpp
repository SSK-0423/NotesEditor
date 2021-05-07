#include "DxLib.h"
#include "WindowSize.hpp"
#include "Bar.hpp"

int Bar::fontHandle;

Bar::Bar(int handle, int i) noexcept : barNum(i) {
	imageHandle = handle;
	GetGraphSize(handle, &width, &height);
	position.x = WINDOW_SIZE_WIDTH / 2;
	position.y = WINDOW_SIZE_HEIGHT / 2 - height * (WINDOW_SIZE_HEIGHT / height) * i;
	collisionPos.x = WINDOW_SIZE_WIDTH / 2;
	collisionPos.y = WINDOW_SIZE_HEIGHT / 2 - height * (WINDOW_SIZE_HEIGHT / height) * i;
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
	DrawFormatStringToHandle(780, position.y + (float)height / 2 - 20, GetColor(255, 255, 255), fontHandle, "%d", barNum+1);
}
