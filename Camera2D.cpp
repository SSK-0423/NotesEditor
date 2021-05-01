#include "Camera2D.hpp"
#include "DxLib.h"
#include "WindowSize.hpp"
#include <math.h>

#define CAMERA_SIZE_WIDTH WINDOW_SIZE_WIDTH / 2
#define CAMERA_SIZE_HEIGHT WINDOW_SIZE_HEIGHT / 2

Camera2D::Camera2D() noexcept {
	position.x = WINDOW_SIZE_WIDTH / 2;
	position.y = WINDOW_SIZE_HEIGHT / 2;
	width = CAMERA_SIZE_WIDTH;
	height = WINDOW_SIZE_HEIGHT;
	collisionPos.x = position.x;
	collisionPos.y = position.y;
	maxPos.x = 0;
	maxPos.y = 0;
	minPos.x = 0;
	minPos.y = 0;
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
	for (auto obj : objList) {
		//カメラに入っているか判定して描画リストに追加
		if (Collision(*obj)) {
			drawList.push_back(obj);
		}
	}
}
//カメラに枠に入ったか判定
bool Camera2D::Collision(const GameObject& obj) const noexcept {
	Vector2D distance;	//距離の格納
	//中心座標の距離
	distance.x = fabsf(this->position.x - obj.collisionPos.x);
	distance.y = fabsf(this->position.y - obj.collisionPos.y);

	Vector2D sizeSum;	//サイズの格納
	//サイズ計算
	sizeSum.x = (this->width + obj.width) / 2.0f;
	sizeSum.y = (this->height + obj.height) / 2.0f;

	// 衝突判定
	if (distance.x <= sizeSum.x && distance.y <= sizeSum.y) {
		//DrawFormatString(0, 100, GetColor(0, 255, 0), "入った");
		return true;
	}
	else {
		//DrawFormatString(0, 100, GetColor(0, 255, 0), "入ってない");
		return false;
	}
}

void Camera2D::DeleteObj() noexcept {
	//GameObjectのメモリ開放
	for (auto obj : objList) {
		delete[] obj;
	}
	objList.clear();
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
		obj->position.y = obj->collisionPos.y - (this->position.y - collisionPos.y);
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
	if (Key[KEY_INPUT_PGDN] != 0 && Key[KEY_INPUT_PGDN] % 15 == 0) {
		position.y += WINDOW_SIZE_HEIGHT;
	}
	if (Key[KEY_INPUT_PGUP] != 0 && Key[KEY_INPUT_PGUP] % 15 == 0) {
		position.y -= WINDOW_SIZE_HEIGHT;
	}	
	if (CheckHitKey(KEY_INPUT_D) != 0) {
		//GameObjectのメモリ開放
		DeleteObj();
	}
}

//移動制限
void Camera2D::PosLimit() noexcept {
	if (position.y < minPos.y) {
		position.y = minPos.y;
	}
	if (position.y > maxPos.y) {
		position.y = maxPos.y;
	}
}

void Camera2D::DebugDraw() noexcept {
	// カメラの座標表示
	DrawFormatString(800, 0, GetColor(0, 255, 0), "x:%f y:%f", position.x, position.y);
	DrawFormatString(800, 150, GetColor(0, 255, 0), "オブジェクト数:%d", objList.size());

	// カメラ枠表示
	/*DrawBox(
		WINDOW_SIZE_WIDTH / 2 - width / 2, WINDOW_SIZE_HEIGHT / 2 - height / 2,
		WINDOW_SIZE_WIDTH / 2 + width / 2, WINDOW_SIZE_HEIGHT / 2 + height / 2,
		GetColor(255, 255, 255), false);*/
}

void Camera2D::SetMinPosition(float x, float y) noexcept {
	minPos.x = x;
	minPos.y = y;
}

void Camera2D::SetMaxPosition(float x, float y) noexcept {
	maxPos.x = x;
	maxPos.y = y;
}

void Camera2D::SetObject(GameObject& obj) noexcept {
	objList.push_back(&obj);
}