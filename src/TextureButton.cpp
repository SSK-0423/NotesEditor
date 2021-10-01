#include "TextureButton.hpp"
#include "Transform.hpp"
#include "Texture.hpp"
#include "ICollider.hpp"
#include "InputDeviceContainer.hpp"
#include "PointWithPolygon.hpp"
#include "Point.hpp"
#include "ColliderCreator.hpp"

// イベント実行
void Engine::UI::TextureButton::RunEventFunc()
{
	if (eventFunc == nullptr)
		return;
	(*eventFunc)();
}

Engine::UI::TextureButton::TextureButton(const char* filePath, Components::COLLIDERTYPE type) : Button()
{
	transform = new Components::Transform();
	texture = new Components::Texture(*transform, filePath);
	collision = new Collision::PointWithPolygon();

	// Collider生成
	collider = Engine::ColliderCreator::Instance().CreateCollider(type, *transform);

	eventFunc = nullptr;

	// Transformをテクスチャのサイズに合わせる
	float texWidth, texHeight;
	texture->GetTextureSize(texWidth, texHeight);
	transform->SetSize(texWidth, texHeight);
	transform->SetPosition(100.f, 100.f);
}

Engine::UI::TextureButton::~TextureButton()
{
	delete transform;
	delete texture;
	delete collider;
	delete collision;
}

void Engine::UI::TextureButton::Update()
{
	// Textureをオブジェクトの位置・回転・サイズに合わせる
	texture->Update();
	// Colliderをオブジェクトの位置・回転・サイズに合わせる
	collider->Update();

	// マウスポインタの座標取得
	float x, y;
	x = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPosX();
	y = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPosY();

	// マウスポインタがボタンの上にあるか
	bool isOnButton = collision->Collision(x, y, *collider);

	//// ボタンクリック時の処理
	if (isOnButton)
	{
		// 左クリックされているか
		bool isClicking = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPressingCount(Engine::Input::Mouse::LEFT_CLICK);
		// 左クリックが離されたか
		bool isRelease = Engine::Input::InputDeviceContainer::Instance().GetMouse().IsReleaseKey(Engine::Input::Mouse::LEFT_CLICK);

		if (isRelease)
		{
			// イベント実行
			RunEventFunc();
		}

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

void Engine::UI::TextureButton::Draw()
{
	texture->Draw();
}