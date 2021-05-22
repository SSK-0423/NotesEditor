#include "Camera2D.hpp"
#include "DxLib.h"
#include "WindowSize.hpp"
#include <math.h>

#define CAMERA_SIZE_WIDTH WINDOW_SIZE_WIDTH / 2
#define CAMERA_SIZE_HEIGHT WINDOW_SIZE_HEIGHT / 2

Camera2D::Camera2D(std::vector<GameObject*>& vec) noexcept : objList(&vec){
	position.x = WINDOW_SIZE_WIDTH / 2;
	position.y = WINDOW_SIZE_HEIGHT / 2;
	width = CAMERA_SIZE_WIDTH;
	height = WINDOW_SIZE_HEIGHT;
	collisionPos.x = position.x;
	collisionPos.y = position.y;
}

//デストラクタ
Camera2D::~Camera2D() noexcept {
	DeleteObj();
}

void Camera2D::Update() noexcept {
	// カメラ内オブジェクトリストを更新
	UpdateDrawList();
	//カメラ内オブジェクトのUpdate実行
	InCameraObjUpdate();
	//キー、マウス操作
	Controll();
	//移動制限
	PosLimit();
}

void Camera2D::Draw() noexcept {
	//デバッグ用文字列などの描画
	DebugDraw();
	//カメラ内オブジェクトの描画
	InCameraObjDraw();
}

//描画オブジェクトリストを更新
void Camera2D::UpdateDrawList() noexcept {
	for (auto obj : *objList) {
		//カメラに入っているか判定して描画リストに追加
		if (Collision(*obj)) {
			drawList.push_back(obj);
		}
	}
}

//カメラに枠に入ったか判定
bool Camera2D::Collision(GameObject& obj) const noexcept {
	Vector2D distance;	//距離の格納
	//中心座標の距離
	distance.x = fabsf(this->position.x - obj.collisionPos.x);
	distance.y = fabsf(this->position.y - obj.collisionPos.y);

	Vector2D sizeSum;	//サイズの格納
	//サイズ計算
	sizeSum.x = (this->width + obj.GetObjWidth()) / 2.0f;
	sizeSum.y = (this->height + obj.GetObjHeight()) / 2.0f;

	// 衝突判定
	if (distance.x <= sizeSum.x && distance.y <= sizeSum.y) {
		return true;
	}
	else {
		return false;
	}
}

void Camera2D::DeleteObj() noexcept {
	objList->clear();
	drawList.clear();
}

//カメラ内オブジェクトの更新処理
void Camera2D::InCameraObjUpdate() noexcept {
	//カメラ内オブジェクトのUpdateを実行
	for (auto obj : drawList) {
		obj->Update();
	}
}

//カメラ内オブジェクトの描画
void Camera2D::InCameraObjDraw() noexcept {
	for (auto obj : drawList)
	{
		obj->position.y = obj->collisionPos.y - (this->position.y - this->collisionPos.y);
		obj->Draw();
	}
	drawList.clear();
}

//キーボード,マウス操作
void Camera2D::Controll() noexcept {
	gpUpdateKey();
	//マウスホイールでスクロール
	position.y += 10 * GetMouseWheelRotVol();
	//上下矢印キーでスクロール
	if (Key[KEY_INPUT_DOWN] != 0) {
		position.y += 5;
	}
	if (Key[KEY_INPUT_UP] != 0) {
		position.y -= 5;
	}

	//PgUp PgDnでウィンドウサイズ分スクロール
	if (Key[KEY_INPUT_PGDN] == 1) {
		position.y += WINDOW_SIZE_HEIGHT;
	}
	if (Key[KEY_INPUT_PGUP] == 1) {
		position.y -= WINDOW_SIZE_HEIGHT;
	}

	//長押しで連続スクロール
	if (Key[KEY_INPUT_PGDN] != 0 && Key[KEY_INPUT_PGDN] % 5 == 0) {
		position.y += WINDOW_SIZE_HEIGHT;
	}
	if (Key[KEY_INPUT_PGUP] != 0 && Key[KEY_INPUT_PGUP] % 5 == 0) {
		position.y -= WINDOW_SIZE_HEIGHT;
	}

	//objListの初期化・GameObjectのdelete
	if (CheckHitKey(KEY_INPUT_D) != 0) {
		//GameObjectのメモリ開放
		DeleteObj();
	}
}

//移動制限
void Camera2D::PosLimit() noexcept {
	if (position.y < minLimitPos.y) {
		position.y = minLimitPos.y;
	}
	if (position.y > maxLimitPos.y) {
		position.y = maxLimitPos.y;
	}
}

void Camera2D::DebugDraw() noexcept {
	unsigned int c = GetColor(0, 255, 0);
	// カメラの座標表示
	DrawFormatString(800, 0, GetColor(0, 255, 0), "x:%f y:%f", position.x, position.y);
	DrawFormatString(800, 150, GetColor(0, 255, 0), "オブジェクト数:%d", objList->size());
	DrawFormatString(800, 250, GetColor(0, 255, 0), "カメラの上端座標:%f",position.y - height/2);
	DrawFormatString(800, 300, GetColor(0, 255, 0), "カメラの下端座標:%f",position.y + height/2);

	// カメラ枠表示
	DrawBox(
		WINDOW_SIZE_WIDTH / 2 - width / 2, WINDOW_SIZE_HEIGHT / 2 - height / 2,
		WINDOW_SIZE_WIDTH / 2 + width / 2, WINDOW_SIZE_HEIGHT / 2 + height / 2,
		GetColor(255, 255, 255), false);
}

void Camera2D::SetMinPosition(float x, float y) noexcept {
	minLimitPos.x = x;
	minLimitPos.y = y;
}

void Camera2D::SetMaxPosition(float x, float y) noexcept {
	maxLimitPos.x = x;
	maxLimitPos.y = y;
}