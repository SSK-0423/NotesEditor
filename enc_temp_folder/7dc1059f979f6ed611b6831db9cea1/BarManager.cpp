#include "BarManager.hpp"
#include "WindowSize.hpp"
#include "Bar.hpp"
#include "DxLib.h"
#define ADD 20

BarManager::BarManager() noexcept {
	SetHandle();
	Bar::fontHandle = CreateFontToHandle("Bar", 30, 1);
}
BarManager::~BarManager() noexcept {
}

void BarManager::SetHandle() noexcept {
	//小節線画像ハンドルの初期化
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

void BarManager::MakeBar(Camera2D& camera, int num) noexcept {
	//小節線オブジェクトの生成
	for (int i = 0; i < num + 2; i++) {
		Bar* bar = new Bar(barHandle[0],i);
		bars.push_back(bar);
		camera.SetObject(*bar);
	}
}

void BarManager::ChangeHandle() noexcept {
	DrawFormatString(800, 250, GetColor(0, 255, 0), "ChangeHandle関数");
	ChangeBarHandle(barHandle[0]);
}
void BarManager::ChangeHandle4() noexcept {
	DrawFormatString(800, 250, GetColor(0, 255, 0), "ChangeHandle4関数");
	ChangeBarHandle(barHandle[1]);
}
void BarManager::ChangeHandle8() noexcept {
	DrawFormatString(800, 250, GetColor(0, 255, 0), "ChangeHandle8関数");
	ChangeBarHandle(barHandle[2]);
}
void BarManager::ChangeHandle16() noexcept {
	DrawFormatString(800, 250, GetColor(0, 255, 0), "ChangeHandle16関数");
	ChangeBarHandle(barHandle[3]);
}
void BarManager::ChangeHandle32() noexcept {
	DrawFormatString(800, 250, GetColor(0, 255, 0), "ChangeHandle32関数");
	ChangeBarHandle(barHandle[4]);
}

void BarManager::ChangeBarHandle(int handle) noexcept {
	for (auto obj : bars) {
		obj->SetHandle(handle);
	}
}
void BarManager::Update() noexcept {
	if (CheckHitKey(KEY_INPUT_D) != 0) {
		DeleteObj();
	}
}
void BarManager::Draw() noexcept {
	DrawFormatString(800,200,GetColor(0,255,0),"小節線数:%d",bars.size());
}
void BarManager::DeleteObj() noexcept {
	bars.clear();
}