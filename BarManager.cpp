#include "BarManager.hpp"
#include "WindowSize.hpp"
#include "Bar.hpp"
#include "Mouse.hpp"
#include "DxLib.h"

BARTYPE BarManager::type;
BarManager::BarManager() noexcept{
	SetHandle();
	Bar::fontHandle = CreateFontToHandle("Bar", 30, 1);
	type = BAR1;
}
BarManager::~BarManager() noexcept {
}

void BarManager::SetHandle() noexcept {
	//���ߐ��摜�n���h���̏�����
	int bar1Handle = LoadGraph("image/Bar.png");
	int bar4Handle = LoadGraph("image/Bar4.png");
	int bar8Handle = LoadGraph("image/Bar8.png");
	int bar16Handle = LoadGraph("image/Bar16.png");
	int bar32Handle = LoadGraph("image/Bar32.png");

	barHandle.push_back(bar1Handle);
	barHandle.push_back(bar4Handle);
	barHandle.push_back(bar8Handle);
	barHandle.push_back(bar16Handle);
	barHandle.push_back(bar32Handle);
}

void BarManager::MakeBar(std::vector<GameObject*>& vec, int num) noexcept {
	//���ߐ��I�u�W�F�N�g�̐���
	for (int i = 0; i < num; i++) {
		Bar* bar = new Bar(barHandle[0],i);
		bars.push_back(bar);
		vec.push_back((GameObject*)bar);
	}
}

void BarManager::ChangeHandle() noexcept {
	ChangeBarHandle(barHandle[0]);
	type = BAR1;
}
void BarManager::ChangeHandle4() noexcept {
	ChangeBarHandle(barHandle[1]);
	type = BAR4;
}
void BarManager::ChangeHandle8() noexcept {
	ChangeBarHandle(barHandle[2]);
	type = BAR8;
}
void BarManager::ChangeHandle16() noexcept {
	ChangeBarHandle(barHandle[3]);
	type = BAR16;
}
void BarManager::ChangeHandle32() noexcept {
	ChangeBarHandle(barHandle[4]);
	type = BAR32;
}

//���ߐ��̉摜�ύX
void BarManager::ChangeBarHandle(int handle) noexcept {
	for (auto obj : bars) {
		obj->SetHandle(handle);
	}
}

void BarManager::Update() noexcept {
	KeyInput();
}

//
void BarManager::Draw() noexcept {
	DrawFormatString(800,200,GetColor(0,255,0),"���ߐ���:%d",bars.size());
}

void BarManager::DeleteObj() noexcept {
	bars.clear();
}

//�L�[���͊֘A
void BarManager::KeyInput() noexcept {
	
	if (CheckHitKey(KEY_INPUT_D) != 0) {
		DeleteObj();
	}
}

//���߂̓����蔻����s
void BarManager::BarsCollision(float& posX, float& posY) noexcept {
	for (auto* obj : bars) {
		Bar* bar = (Bar*)obj;
		bar->Collision(posX, posY);
	}
}

BARTYPE BarManager::GetBarType() noexcept {
	return type;
}

void BarManager::DecidePutPos(float& posX, float& posY) noexcept {
	BarsCollision(posX, posY);
}