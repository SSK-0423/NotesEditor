#include "MultiTextureButton.hpp"
#include "TextureButton.hpp"

#include "Transform.hpp"
#include "Texture.hpp"
#include "ICollider.hpp"
#include "InputDeviceContainer.hpp"
#include "PointWithPolygon.hpp"
#include "Point.hpp"
#include "ColliderCreator.hpp"

#include "GameSymbol.hpp"

void Engine::UI::MultiTextureButton::RunEventFunc()
{
	if (eventFunc == nullptr)
		return;
	(*eventFunc)();
}

Engine::UI::MultiTextureButton::MultiTextureButton() : clickCount(0)
{
	nowButton = nullptr;
}
Engine::UI::MultiTextureButton::MultiTextureButton(std::vector<const char*> filePath, Components::COLLIDERTYPE type) : clickCount(0)
{
	transform = new Components::Transform();
	for (auto& path : filePath)
	{
		texture.push_back(new Components::Texture(*transform, path));
	}
	collision = new Collision::PointWithPolygon();

	eventFunc = nullptr;

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
	for (auto& tex : texture)
	{
		delete tex;
	}
	texture.clear();
	texture.shrink_to_fit();
	delete transform;
	delete collider;
	delete collision;
}

void Engine::UI::MultiTextureButton::AddTextureButton(TextureButton* button)
{
	if (nowButton == nullptr)
		nowButton = button;
	textureButtonList.push_back(button);
}

void Engine::UI::MultiTextureButton::SetEventFunc(DelegateBase<void(void)>* func)
{
	eventFunc = func;
}

void Engine::UI::MultiTextureButton::Update()
{
	collider->Update();
	texture[clickCount % texture.size()]->Update();

	// マウスポインタの座標取得
	float x, y;
	x = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPosX();
	y = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPosY();

	// マウスポインタがボタンの上にあるか
	bool isOnButton = collision->Collision(x, y, *collider);
	// ボタンクリック時の処理
	if (isOnButton)
	{
		// 左クリックが離されたか
		bool isRelease = Engine::Input::InputDeviceContainer::Instance().GetMouse().IsReleaseKey(Engine::Input::Mouse::LEFT_CLICK);
		if (isRelease)
		{
			// イベント実行
			RunEventFunc();
			clickCount++;
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


	//if (nowButton == nullptr)
	//	return;
	//textureButtonList[clickCount % textureButtonList.size()]->Update();
}

void Engine::UI::MultiTextureButton::Draw()
{
	texture[clickCount % texture.size()]->Draw();
	//if (nowButton == nullptr)
	//	return;
	//textureButtonList[clickCount % textureButtonList.size()]->Draw();
}
