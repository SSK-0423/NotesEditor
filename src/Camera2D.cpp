#include "Camera2D.hpp"
#include "Transform.hpp"
#include "WindowSize.hpp"
#include "InputDeviceContainer.hpp"
#include "NotesEditorMusic.hpp"
#include "DxLib.h"
#include <algorithm>
#include <math.h>

const float CAMERA_WIDTH = static_cast<float>(WINDOW_SIZE_WIDTH) / 2.f;
const float CAMERA_HEIGHT = static_cast<float>(WINDOW_SIZE_HEIGHT);

Engine::Camera2D::Camera2D(std::vector<Engine::GameObject*>& objList) : objList(objList)
{
	transform = new Components::Transform();
	transform->SetPosition(CAMERA_WIDTH, CAMERA_HEIGHT / 2.f);
	transform->SetSize(CAMERA_WIDTH, CAMERA_HEIGHT);
}

//デストラクタ
Engine::Camera2D::~Camera2D()
{
	DeleteObj();
}

void Engine::Camera2D::Update()
{
	UpdateOrigin();
	UpdateDrawList();
	UpdateInCameraObj();
	Input();
	LimitPos();
	AutoScroll();
}

void Engine::Camera2D::Draw()
{
	DrawInCameraObj();
}

void Engine::Camera2D::UpdateDrawList()
{
	drawList.clear();
	drawList.shrink_to_fit();

	for (auto& obj : objList)
	{
		if (Collision(*obj))
		{
			drawList.push_back(obj);
		}
	}
}

void Engine::Camera2D::AutoScroll()
{
	NotesEditor::NotesEditorMusic music = NotesEditor::NotesEditorMusic::Instance();
	if (music.IsPlaying())
	{
		// 1小節の縦幅 / ((60 * beat * speed / bpm)  * 60) = 1フレームの移動幅
		float frame_move = WINDOW_SIZE_HEIGHT / (music.GetBeat() * (60 / music.GetBPM()) * 60);
		transform->SetPosition(WINDOW_SIZE_WIDTH / 2, -frame_move * music.GetElapsedTime() / 1000.0f * 60.0f + WINDOW_SIZE_HEIGHT / 2);
	}
}

//カメラに枠に入ったか判定
bool Engine::Camera2D::Collision(const GameObject& obj)
{
	const Components::Transform& targetTransform = obj.GetTransform();
	Vector2<float> distance = CalcDistance(targetTransform);
	Components::Size sizeSum = SumSize(targetTransform);

	if (distance.x <= sizeSum.width && distance.y <= sizeSum.height)
		return true;
	return false;
}

Vector2<float> Engine::Camera2D::CalcDistance(const Components::Transform& targetTransform)
{
	Vector2<float> distance;
	Components::Position targetPos = targetTransform.GetPosition();
	Components::Position cameraPos = transform->GetPosition();

	// 中心座標の距離
	distance.x = fabsf(cameraPos.x - targetPos.x);
	distance.y = fabsf(cameraPos.y - targetPos.y);

	return distance;
}

Engine::Components::Size Engine::Camera2D::SumSize(const Components::Transform& targetTransform)
{
	Components::Size sizeSum;
	Components::Size targetSize = targetTransform.GetSize();
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

Engine::Components::Position Engine::Camera2D::GetOriginPos()
{
	return origin;
}

void Engine::Camera2D::UpdateOrigin()
{
	origin.x = transform->GetPosition().x - WINDOW_SIZE_WIDTH / 2.f;
	origin.y = transform->GetPosition().y - WINDOW_SIZE_HEIGHT / 2.f;
}

//カメラ内オブジェクトの更新処理
void Engine::Camera2D::UpdateInCameraObj()
{
	for (auto obj : drawList)
	{
		float x = obj->GetTransform().GetPosition().x - origin.x;
		float y = obj->GetTransform().GetPosition().y - origin.y;
		Components::Position updatedPos(x, y);
		obj->UpdateScreenPos(updatedPos);
		obj->Update();
	}
}

//カメラ内オブジェクトの描画
void Engine::Camera2D::DrawInCameraObj()
{
	for (auto obj : drawList)
		obj->Draw();
}

//キーボード,マウス操作
void Engine::Camera2D::Input()
{
	Components::Position cameraPos = transform->GetPosition();

	NotesEditor::NotesEditorMusic& music = NotesEditor::NotesEditorMusic::Instance();
	// bpm:1分間の当たりの拍数
	// beat:1小節
	// 1拍の長さ
	float beatTimeLength = 60.f / static_cast<float>(music.GetBPM());
	// 1小節の長さ
	float barTimeLength = 60.f / static_cast<float>(music.GetBPM()) * 4;
	// 1/32音符の長さ
	//float note32TimeLength = beatTimeLength / 32.f;
	float note32TimeLength = static_cast<float>(WINDOW_SIZE_HEIGHT) / 32.f;
	//マウスホイールでスクロール
	//cameraPos.y += 10 * GetMouseWheelRotVol();
	cameraPos.y += note32TimeLength * GetMouseWheelRotVol();
	if (Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_DOWN))
		cameraPos.y += note32TimeLength;
	if (Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_UP))
		cameraPos.y -= note32TimeLength;

	//PgUp PgDnでウィンドウサイズ分スクロール
	if (Input::InputDeviceContainer::Instance().GetKeyboard().IsPressKey(KEY_INPUT_PGDN))
		cameraPos.y += CAMERA_HEIGHT;
	if (Input::InputDeviceContainer::Instance().GetKeyboard().IsPressKey(KEY_INPUT_PGUP))
		cameraPos.y -= CAMERA_HEIGHT;

	//長押しで連続スクロール
	if (Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_PGDN) > 31
		&& Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_PGDN) % 5 == 0)
		cameraPos.y += CAMERA_HEIGHT;
	if (Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_PGUP) > 31
		&& Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_PGUP) % 5 == 0)
		cameraPos.y -= CAMERA_HEIGHT;

	// 更新後の座標セット
	transform->SetPosition(cameraPos.x, cameraPos.y);
}

//移動制限
void Engine::Camera2D::LimitPos()
{
	Components::Position cameraPos = transform->GetPosition();
	transform->SetPosition(cameraPos.x, (std::max)(cameraPos.y, minLimitPos.y));
	//transform->SetPosition(cameraPos.x, (std::min)(cameraPos.y, maxLimitPos.y));
}

void Engine::Camera2D::SetMinPosition(float x, float y)
{
	minLimitPos.x = x;
	minLimitPos.y = y;
}

void Engine::Camera2D::SetMaxPosition(float x, float y)
{
	maxLimitPos.x = x;
	maxLimitPos.y = y;
}