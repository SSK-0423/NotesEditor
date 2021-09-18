#include "Camera2D.hpp"
#include "DxLib.h"
#include "Transform.hpp"
#include "WindowSize.hpp"
#include <math.h>

const float CAMERA_WIDTH = WINDOW_SIZE_WIDTH / 2.f;
const float CAMERA_HEIGHT = WINDOW_SIZE_HEIGHT / 2.f;

Camera2D::Camera2D(std::vector<std::vector<GameObject*>*>& vec) noexcept : objList(&vec)
{
	Position2D<float> initPos;
	initPos.x = WINDOW_SIZE_WIDTH / 2.f;
	initPos.y = WINDOW_SIZE_HEIGHT / 2.f;
	transform.SetPosition(initPos);

	Size2D<float> initSize;
	initSize.width = WINDOW_SIZE_WIDTH / 2.f;
	initSize.height = WINDOW_SIZE_HEIGHT / 2.f;
	transform.SetSize(initSize);
}

//デストラクタ
Camera2D::~Camera2D() noexcept 
{
	DeleteObj();
}

void Camera2D::Update() noexcept 
{
	UpdateOrigin();
	// カメラ内オブジェクトリストを更新
	UpdateDrawList();
	//カメラ内オブジェクトのUpdate実行
	UpdateInCameraObj();
	//キー、マウス操作
	Controll();
	//移動制限
	LimitPos();
}

void Camera2D::Draw() noexcept 
{
	//デバッグ用文字列などの描画
	DebugDraw();
	//カメラ内オブジェクトの描画
	DrawInCameraObj();
}

void Camera2D::Input() noexcept
{
}

//描画オブジェクトリストを更新
void Camera2D::UpdateDrawList() noexcept 
{
	for (auto list : *objList) 
	{
		//DrawFormatString(700, 225, GetColor(0, 255, 0), "size:%d",list->size());
		for (auto obj : *list) 
		{
			//カメラに入っているか判定して描画リストに追加
			if (Collision(*obj)) 
			{
				drawList.push_back(obj);
			}
		}
	}
}

//カメラに枠に入ったか判定
bool Camera2D::Collision(const GameObject& obj) noexcept 
{
	// ターゲットのTransform
	const Transform& targetTransform = obj.GetTransform();
	// 距離の格納
	Vector2<float> distance = CalcDistance(targetTransform);
	// サイズの合計値格納
	Vector2<float> sizeSum = SumSize(targetTransform);

	// 衝突判定
	if (distance.x <= sizeSum.x && distance.y <= sizeSum.y)
		return true;
	return false;

	const int a = 10;
	int b = a;
}

Vector2<float> Camera2D::CalcDistance(const Transform& targetTransform)
{
	// 距離の格納
	Vector2<float> distance;
	// ターゲットの座標
	Position2D<float> targetPos = targetTransform.GetPosition();
	// カメラの座標
	Position2D<float> cameraPos = transform.GetPosition();
	
	// 中心座標の距離
	distance.x = fabsf(cameraPos.x - targetPos.x);
	distance.y = fabsf(cameraPos.y - targetPos.y);

	return distance;
}

Vector2<float> Camera2D::SumSize(const Transform& targetTransform)
{
	// サイズの合計値格納
	Vector2<float> sizeSum;
	
	// ターゲットのサイズ
	Size2D<float> targetSize = targetTransform.GetSize();
	// カメラのサイズ
	Size2D<float> cameraSize = transform.GetSize();

	// サイズ計算
	sizeSum.x = (cameraSize.width + targetSize.width) / 2.f;
	sizeSum.y = (cameraSize.height + targetSize.height) / 2.f;

	return sizeSum;
}

void Camera2D::DeleteObj() noexcept {
	drawList.clear();
	drawList.shrink_to_fit();
}

void Camera2D::UpdateOrigin()
{
	origin.x = transform.GetPosition().x -  WINDOW_SIZE_WIDTH / 2;
	origin.y = transform.GetPosition().y - WINDOW_SIZE_HEIGHT / 2;
}

//カメラ内オブジェクトの更新処理
void Camera2D::UpdateInCameraObj() noexcept 
{
	//カメラ内オブジェクトのUpdateを実行
	for (auto obj : drawList) 
	{
		obj->Update();
	}
}

//カメラ内オブジェクトの描画
void Camera2D::DrawInCameraObj() noexcept 
{
	for (auto obj : drawList)
	{
		//obj->position.y = obj->collisionPos.y - (this->position.y - this->collisionPos.y);
		// スクリーン座標に変換

		obj->Draw();
	}
	drawList.clear();
}

//キーボード,マウス操作
void Camera2D::Controll() noexcept 
{
	gpUpdateKey();
	// カメラの座標
	Position2D<float> cameraPos = transform.GetPosition();

	//マウスホイールでスクロール
	cameraPos.y += 10 * GetMouseWheelRotVol();

	//上下矢印キーでスクロール
	if (Key[KEY_INPUT_DOWN] != 0) 
	{
		cameraPos.y += 5;
	}
	if (Key[KEY_INPUT_UP] != 0) 
	{
		cameraPos.y -= 5;
	}

	//PgUp PgDnでウィンドウサイズ分スクロール
	if (Key[KEY_INPUT_PGDN] == 1) 
	{
		cameraPos.y += WINDOW_SIZE_HEIGHT;
	}
	if (Key[KEY_INPUT_PGUP] == 1) 
	{
		cameraPos.y -= WINDOW_SIZE_HEIGHT;
	}

	//長押しで連続スクロール
	if (Key[KEY_INPUT_PGDN] != 0 && Key[KEY_INPUT_PGDN] % 5 == 0) 
	{
		cameraPos.y += WINDOW_SIZE_HEIGHT;
	}
	if (Key[KEY_INPUT_PGUP] != 0 && Key[KEY_INPUT_PGUP] % 5 == 0) 
	{
		cameraPos.y -= WINDOW_SIZE_HEIGHT;
	}

	// 更新後の座標セット
	transform.SetPosition(cameraPos);
}

//移動制限
void Camera2D::LimitPos() noexcept
{
	Position2D<float> cameraPos = transform.GetPosition();

	if (cameraPos.y < minLimitPos.y)
	{
		cameraPos.y = minLimitPos.y;
	}
	if (cameraPos.y > maxLimitPos.y)
	{
		cameraPos.y = maxLimitPos.y;
	}
}

void Camera2D::DebugDraw() noexcept
{
	Position2D<float> cameraPos = transform.GetPosition();
	Size2D<float> cameraSize = transform.GetSize();

	Color color = GetColor(0, 255, 0);
	// カメラの座標表示
	DrawFormatString(800, 0, color, "x:%f y:%f", cameraPos.x, cameraPos.y);
	DrawFormatString(800, 125, color, "objListサイズ:%d", objList->size());
	DrawFormatString(800, 150, color, "小節オブジェクト数:%d", objList[0][0]->size());
	DrawFormatString(800, 175, color, "ノーツオブジェクト数:%d", objList[0][1]->size());
	DrawFormatString(800, 250, color, "カメラの上端座標:%f", cameraPos.y - cameraSize.height / 2.f);
	DrawFormatString(800, 300, color, "カメラの下端座標:%f", cameraPos.y + cameraSize.height / 2.f);

	// カメラ枠表示
	DrawBox(
		WINDOW_SIZE_WIDTH / 2 - cameraSize.width / 2, WINDOW_SIZE_HEIGHT / 2 - cameraSize.height / 2,
		WINDOW_SIZE_WIDTH / 2 + cameraSize.width / 2, WINDOW_SIZE_HEIGHT / 2 + cameraSize.height / 2,
		GetColor(255, 255, 255), false);
}

void Camera2D::SetMinposition(float x, float y) noexcept
{
	minLimitPos.x = x;
	minLimitPos.y = y;
}

void Camera2D::SetMaxposition(float x, float y) noexcept
{
	maxLimitPos.x = x;
	maxLimitPos.y = y;
}