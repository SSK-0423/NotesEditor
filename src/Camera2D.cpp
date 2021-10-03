#include "Camera2D.hpp"
#include "DxLib.h"
#include "transform.hpp"
#include "WindowSize.hpp"
#include "InputDeviceContainer.hpp"
#include "TestObject.h"
#include <math.h>

const float CAMERA_WIDTH = WINDOW_SIZE_WIDTH / 2.f;
const float CAMERA_HEIGHT = WINDOW_SIZE_HEIGHT / 2.f;

Engine::Camera2D::Camera2D()
{
	objList = nullptr;
	transform = new Components::Transform();
	transform->SetPosition(WINDOW_SIZE_WIDTH / 2.f, WINDOW_SIZE_HEIGHT / 2.f);
	transform->SetSize(WINDOW_SIZE_WIDTH / 2.f, WINDOW_SIZE_HEIGHT);
}

Engine::Camera2D::Camera2D(std::vector<std::vector<GameObject*>*>& vec) : objList(&vec)
{
	transform = new Components::Transform();
	transform->SetPosition(WINDOW_SIZE_WIDTH / 2.f, WINDOW_SIZE_HEIGHT / 2.f);
	transform->SetSize(WINDOW_SIZE_WIDTH / 2.f, WINDOW_SIZE_HEIGHT);
}

//デストラクタ
Engine::Camera2D::~Camera2D()
{
	DeleteObj();
}

void Engine::Camera2D::Update()
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

void Engine::Camera2D::Draw()
{
	//デバッグ用文字列などの描画
	DebugDraw();
	//カメラ内オブジェクトの描画
	DrawInCameraObj();
}

//描画オブジェクトリストを更新
void Engine::Camera2D::UpdateDrawList()
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
bool Engine::Camera2D::Collision(const GameObject& obj)
{
	// ターゲットのTransform
	const Components::Transform& targetTransform = obj.GetTransform();
	// 距離の格納
	Vector2<float> distance = CalcDistance(targetTransform);
	// サイズの合計値格納
	Components::Size sizeSum = SumSize(targetTransform);

	// 衝突判定
	if (distance.x <= sizeSum.width && distance.y <= sizeSum.height)
		return true;
	return false;
}

Vector2<float> Engine::Camera2D::CalcDistance(const Components::Transform& targetTransform)
{
	// 距離の格納
	Vector2<float> distance;
	// ターゲットの座標
	Components::Position targetPos = targetTransform.GetPosition();
	// カメラの座標
	Components::Position cameraPos = targetTransform.GetPosition();

	// 中心座標の距離
	distance.x = fabsf(cameraPos.x - targetPos.x);
	distance.y = fabsf(cameraPos.y - targetPos.y);

	return distance;
}

Engine::Components::Size Engine::Camera2D::SumSize(const Components::Transform& targetTransform)
{
	// サイズの合計値格納
	Components::Size sizeSum;
	// ターゲットのサイズ
	Components::Size targetSize = targetTransform.GetSize();
	// カメラのサイズ
	Components::Size cameraSize = transform->GetSize();

	// サイズ計算
	sizeSum.width = (cameraSize.width + targetSize.width) / 2.f;
	sizeSum.height = (cameraSize.height + targetSize.height) / 2.f;

	return sizeSum;
}

void Engine::Camera2D::DeleteObj() 
{
	drawList.clear();
	drawList.shrink_to_fit();
}

void Engine::Camera2D::UpdateOrigin()
{
	origin.x = transform->GetPosition().x - WINDOW_SIZE_WIDTH / 2.f;
	origin.y = transform->GetPosition().y - WINDOW_SIZE_HEIGHT / 2.f;
}

//カメラ内オブジェクトの更新処理
void Engine::Camera2D::UpdateInCameraObj()
{
	//カメラ内オブジェクトのUpdateを実行
	for (auto obj : drawList)
	{
		obj->Update();
	}
}

//カメラ内オブジェクトの描画
void Engine::Camera2D::DrawInCameraObj()
{
	for (auto obj : drawList)
	{
		//obj->position.y = obj->collisionPos.y - (this->position.y - this->collisionPos.y);
		// スクリーン座標に変換
		float x = obj->GetTransform().GetPosition().x - origin.x;
		float y = obj->GetTransform().GetPosition().y - origin.y;
		Components::Position updatedPos(x, y);
		obj->UpdateScreenPos(updatedPos);
		obj->Draw();
	}
	drawList.clear();
}

//キーボード,マウス操作
void Engine::Camera2D::Controll()
{
	// カメラの座標
	Components::Position cameraPos = transform->GetPosition();

	//マウスホイールでスクロール
	cameraPos.y += 10 * GetMouseWheelRotVol();

	if (Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_DOWN))
		cameraPos.y += 5.f;
	if (Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_UP))
		cameraPos.y -= 5.f;

	//PgUp PgDnでウィンドウサイズ分スクロール
	if (Input::InputDeviceContainer::Instance().GetKeyboard().IsPressKey(KEY_INPUT_PGDN))
		cameraPos.y += WINDOW_SIZE_HEIGHT;
	if (Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_PGUP))
		cameraPos.y -= WINDOW_SIZE_HEIGHT;

	//長押しで連続スクロール
	if (Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_PGDN)
		&& Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_PGDN) % 5 == 0)
		cameraPos.y += WINDOW_SIZE_HEIGHT;
	if (Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_PGUP)
		&& Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_PGUP) % 5 == 0)
		cameraPos.y -= WINDOW_SIZE_HEIGHT;

	// 更新後の座標セット
	transform->SetPosition(cameraPos.x, cameraPos.y);
}

//移動制限
void Engine::Camera2D::LimitPos()
{
	Components::Position cameraPos = transform->GetPosition();

	if (cameraPos.y < minLimitPos.y)
	{
		cameraPos.y = minLimitPos.y;
	}
	if (cameraPos.y > maxLimitPos.y)
	{
		cameraPos.y = maxLimitPos.y;
	}
}

void Engine::Camera2D::DebugDraw()
{
	Components::Position cameraPos = transform->GetPosition();
	Components::Size cameraSize = transform->GetSize();

	Color color = GetColor(0, 255, 0);
	// カメラの座標表示
	DrawFormatString(800, 0, color, "x:%f y:%f", cameraPos.x, cameraPos.y);
	DrawFormatString(800, 125, color, "objListサイズ:%d", objList->size());
	//DrawFormatString(800, 150, color, "小節オブジェクト数:%d", objList[0][0]->size());
	//DrawFormatString(800, 175, color, "ノーツオブジェクト数:%d", objList[0][1]->size());
	DrawFormatString(800, 250, color, "カメラの上端座標:%f", cameraPos.y - cameraSize.height / 2.f);
	DrawFormatString(800, 300, color, "カメラの下端座標:%f", cameraPos.y + cameraSize.height / 2.f);

	// カメラ枠表示
	DrawBox(
		WINDOW_SIZE_WIDTH / 2 - cameraSize.width / 2, WINDOW_SIZE_HEIGHT / 2 - cameraSize.height / 2,
		WINDOW_SIZE_WIDTH / 2 + cameraSize.width / 2, WINDOW_SIZE_HEIGHT / 2 + cameraSize.height / 2,
		GetColor(255, 255, 255), false);
}

void Engine::Camera2D::SetMinposition(float x, float y)
{
	minLimitPos.x = x;
	minLimitPos.y = y;
}

void Engine::Camera2D::SetMaxposition(float x, float y)
{
	maxLimitPos.x = x;
	maxLimitPos.y = y;
}