#include "BarManager.hpp"
#include "WindowSize.hpp"
#include "DxLib.h"
#define ADD 20

BarManager::BarManager() {
}
BarManager::~BarManager() {
}

void BarManager::SetObject(GameObject* bar) {
	bars.push_back(bar);
}

void BarManager::SetHandle(int& handle) {
	barHandle.push_back(handle);
	DrawFormatString(800, 250, GetColor(0, 255, 0), "BarManager�֐�");
}

void BarManager::ChangeHandle() {
	DrawFormatString(800, 250, GetColor(0, 255, 0), "ChangeHandle�֐�");
	ChangeBarHandle(barHandle[0]);
}
void BarManager::ChangeHandle4() {
	DrawFormatString(800, 250, GetColor(0, 255, 0), "ChangeHandle4�֐�");
	ChangeBarHandle(barHandle[1]);
}
void BarManager::ChangeHandle8() {
	DrawFormatString(800, 250, GetColor(0, 255, 0), "ChangeHandle8�֐�");
	ChangeBarHandle(barHandle[2]);
}
void BarManager::ChangeHandle16() {
	DrawFormatString(800, 250, GetColor(0, 255, 0), "ChangeHandle16�֐�");
	ChangeBarHandle(barHandle[3]);
}
void BarManager::ChangeHandle32() {
	DrawFormatString(800, 250, GetColor(0, 255, 0), "ChangeHandle32�֐�");
	ChangeBarHandle(barHandle[4]);
}

void BarManager::ChangeBarHandle(int handle) {
	for (auto i : bars) {
		i->SetHandle(handle);
	}
}
void BarManager::Update() {
	if (CheckHitKey(KEY_INPUT_D) != 0) {
		DeleteObj();
	}
}
void BarManager::Draw() {
	DrawFormatString(800,200,GetColor(0,255,0),"���ߐ���:%d",bars.size());
}
void BarManager::DeleteObj() {
	bars.clear();
}

Bar::Bar(int handle, int i) {
	barNum = i;
	imageHandle = handle;
	GetGraphSize(handle, &width, &height);
	position.x = WINDOW_SIZE_WIDTH / 2;
	position.y = WINDOW_SIZE_HEIGHT / 2 - height * (WINDOW_SIZE_HEIGHT / height) *i;
	collisionPos.x = WINDOW_SIZE_WIDTH / 2;
	collisionPos.y = WINDOW_SIZE_HEIGHT / 2 - height * (WINDOW_SIZE_HEIGHT / height) * i;
	//height = 1024;
}
Bar::~Bar() {

}
void Bar::Update() {
}
void Bar::Draw() {
	DrawModiGraph(
		position.x - width / 2, position.y - height / 2, //������W
		position.x + width / 2, position.y - height / 2, //�E����W
		position.x + width / 2, position.y + height / 2, //�E�����W
		position.x - width / 2, position.y + height / 2, //�������W
		imageHandle, true); //�O���t�B�b�N�n���h���A���ߏ���
}
void Bar::SetHandle(int handle) {
	imageHandle = handle;
}
