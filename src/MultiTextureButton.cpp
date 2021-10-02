#include "MultiTextureButton.hpp"
#include "Transform.hpp"
#include "Texture.hpp"
#include "ICollider.hpp"
#include "InputDeviceContainer.hpp"
#include "PointWithPolygon.hpp"
#include "Point.hpp"
#include "ColliderCreator.hpp"

void Engine::UI::MultiTextureButton::RunEventFunc()
{
}

Engine::UI::MultiTextureButton::MultiTextureButton(const char* filePath, Components::COLLIDERTYPE type) : Button()
{
	transform = new Components::Transform();
	texture.push_back(new Components::Texture(*transform, filePath));
	collision = new Collision::PointWithPolygon();

	// Collider生成
	collider = Engine::ColliderCreator::Instance().CreateCollider(type, *transform);

	// Transformをテクスチャのサイズに合わせる
	float texWidth, texHeight;
	texture[0]->GetTextureSize(texWidth, texHeight);
	transform->SetSize(texWidth, texHeight);
	transform->SetPosition(100.f, 100.f);
}

Engine::UI::MultiTextureButton::~MultiTextureButton()
{
}

void Engine::UI::MultiTextureButton::AddTexture(const char* filePath)
{
	texture.push_back(new Components::Texture(*transform, filePath));
}

void Engine::UI::MultiTextureButton::Update()
{
	// マウスポインタの座標取得
	float x, y;
	x = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPosX();
	y = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPosY();

	// マウスポインタがボタンの上にあるか
	bool isOnButton =  collision->Collision(x, y, *collider);
	// ボタンクリック時の処理
	if (isOnButton)
	{
		// 左クリックが離されたか
		bool isRelease = Engine::Input::InputDeviceContainer::Instance().GetMouse().IsReleaseKey(Engine::Input::Mouse::LEFT_CLICK);
		if (isRelease)
		{
			// イベント実行
			RunEventFunc();
		}

		// 左クリックされているか
		bool isClicking = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPressingCount(Engine::Input::Mouse::LEFT_CLICK);
		if (isClicking)
		{
			// ボタンサイズ変更
			transform->Scaling(CLICKEDSIZE, CLICKEDSIZE);
			return;
		}
	}

	// ボタンを元の大きさに戻す
	transform->Scaling(1.0f, 1.0f);
}

void Engine::UI::MultiTextureButton::Draw()
{
}
