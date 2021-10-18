#include "MultiTextureButton.hpp"
#include "TextureButton.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "ICollider.hpp"
#include "PointWithPolygon.hpp"
#include "Point.hpp"
#include "ColliderCreator.hpp"
#include "GameUtility.hpp"

Engine::UI::MultiTextureButton::MultiTextureButton(std::vector<const char*> filePath, Components::COLLIDERTYPE type)
	: Button(type), nowTexIndex(0), clickCount(0), eventFunc(nullptr)
{
	for (auto& path : filePath)
	{
		textures.push_back(new Components::Texture(*transform, path));
	}
}

Engine::UI::MultiTextureButton::~MultiTextureButton()
{
	for (auto& tex : textures)
		delete tex;
	textures.clear();
	textures.shrink_to_fit();
}

void Engine::UI::MultiTextureButton::SetEventFunc(DelegateBase<void(void)>* func)
{
	eventFunc = func;
}

void Engine::UI::MultiTextureButton::Update()
{
	UpdateNowTexIndex();
	textures[nowTexIndex]->Update();
	collider->Update();
	if (IsClicked())
		OnClick();
}

void Engine::UI::MultiTextureButton::Draw()
{
	textures[nowTexIndex]->Draw();
}

void Engine::UI::MultiTextureButton::UpdateNowTexIndex()
{
	nowTexIndex = clickCount % textures.size();
}

void Engine::UI::MultiTextureButton::RunEventFunc()
{
	if (eventFunc == nullptr)
		return;
	(*eventFunc)();
}

void Engine::UI::MultiTextureButton::OnClick()
{
	RunEventFunc();
	clickCount++;
}

void Engine::UI::MultiTextureButton::Release()
{
	isPressed = false;
}

void Engine::UI::MultiTextureButton::Clicking()
{
	isPressed = true;
	transform->Scaling(CLICKEDSIZE, CLICKEDSIZE);
}

void Engine::UI::MultiTextureButton::NotOnButton()
{
	transform->Scaling(1.f, 1.f);
}
