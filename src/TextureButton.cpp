#include "TextureButton.hpp"
#include "Transform.hpp"
#include "Texture.hpp"
#include "ICollider.hpp"
#include "InputDeviceContainer.hpp"
#include "PointWithPolygon.hpp"
#include "Point.hpp"
#include "ColliderCreator.hpp"

Engine::UI::TextureButton::TextureButton(const char* filePath, Components::COLLIDERTYPE type) : Button(type)
{
	texture = new Components::Texture(*transform, filePath);
	eventFunc = nullptr;

	// Transformをテクスチャのサイズに合わせる
	float texWidth, texHeight;
	texture->GetTextureSize(texWidth, texHeight);
	transform->SetSize(texWidth, texHeight);
}

Engine::UI::TextureButton::~TextureButton()
{
	delete texture;
}

void Engine::UI::TextureButton::SetEventFunc(DelegateBase<void(void)>* func)
{
	eventFunc = func;
}

void Engine::UI::TextureButton::Update()
{
	texture->Update();
	collider->Update();
	if (IsClicked())
		OnClick();
}

void Engine::UI::TextureButton::Draw()
{
	texture->Draw();
}

// イベント実行
void Engine::UI::TextureButton::RunEventFunc()
{
	if (eventFunc == nullptr)
		return;
	(*eventFunc)();
}

void Engine::UI::TextureButton::OnClick()
{
	RunEventFunc();
}

void Engine::UI::TextureButton::Release()
{
	isPressed = false;
}

void Engine::UI::TextureButton::Clicking()
{
	isPressed = true;
	transform->Scaling(CLICKEDSIZE, CLICKEDSIZE);
}

void Engine::UI::TextureButton::NotOnButton()
{
	transform->Scaling(1.f, 1.f);
}

