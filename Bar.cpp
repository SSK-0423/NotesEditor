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
		position.x - (float)width / 2, position.y - (float)height / 2, //������W
		position.x + (float)width / 2, position.y - (float)height / 2, //�E����W
		position.x + (float)width / 2, position.y + (float)height / 2, //�E�����W
		position.x - (float)width / 2, position.y + (float)height / 2, //�������W
		imageHandle, true); //�O���t�B�b�N�n���h���A���ߏ���
	DrawFormatStringToHandle(780, position.y + (float)height / 2 - 20, GetColor(255, 255, 255), fontHandle, "%d", barNum+1);
}
