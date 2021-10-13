#include "TextureButton.hpp"
#include "Transform.hpp"
#include "Texture.hpp"
#include "ICollider.hpp"
#include "InputDeviceContainer.hpp"
#include "PointWithPolygon.hpp"
#include "Point.hpp"
#include "ColliderCreator.hpp"

Engine::UI::TextureButton::TextureButton(const char* filePath, Components::COLLIDERTYPE type) : Button(), isPressed(false)
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
}

Engine::UI::TextureButton::~TextureButton()
{
	delete transform;
	delete texture;
	delete collider;
	delete collision;
}

void Engine::UI::TextureButton::SetEventFunc(DelegateBase<void(void)>* func)
{
	eventFunc = func;
}

void Engine::UI::TextureButton::Update()
{
	// Textureをオブジェクトの位置・回転・サイズに合わせる
	texture->Update();
	// Colliderをオブジェクトの位置・回転・サイズに合わせる
	collider->Update();

	if (IsClick())
		RunEventFunc();
}

void Engine::UI::TextureButton::Draw()
{
	texture->Draw();
}

bool Engine::UI::TextureButton::IsClick()
{
	if (IsOnButton())
	{
		// ボタンがクリックされている状態で左クリックが離されたか
		bool isRelease = Engine::Input::InputDeviceContainer::Instance().GetMouse().IsReleaseKey(Engine::Input::Mouse::LEFT_CLICK);
		if (isRelease && isPressed == true)
		{
			isPressed = false;
			return true;
		}

		// 左クリックされているか
		bool isClicking = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPressingCount(Engine::Input::Mouse::LEFT_CLICK);
		if (isClicking)
		{
			isPressed = true;
			transform->Scaling(CLICKEDSIZE, CLICKEDSIZE);
			return false;
		}
	}
	transform->Scaling(1.f,1.f);
	return false;
}

// イベント実行
void Engine::UI::TextureButton::RunEventFunc()
{
	if (eventFunc == nullptr)
		return;
	(*eventFunc)();
}

bool Engine::UI::TextureButton::IsOnButton()
{
	// マウスポインタの座標取得
	float x, y;
	x = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPosX();
	y = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPosY();

	// マウスポインタがボタンの上にあるか
	return collision->Collision(x, y, *collider);
}