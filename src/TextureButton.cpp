#include "TextureButton.hpp"
#include "Transform.hpp"
#include "Texture.hpp"
#include "ICollider.hpp"
#include "PointWithPolygon.hpp"
#include "InputDeviceContainer.hpp"
#include "ColliderCreator.hpp"

UI::TextureButton::TextureButton(const char* filePath, Component::Collider::COLLIDERTYPE type)
{
	transform = new Component::Transform(); 
	texture = new Component::Texture(*transform,filePath);
	collision = new Component::Collision::PointWithPolygon();

	// Transformをテクスチャのサイズに合わせる
	float texWidth, texHeight;
	texture->GetTextureSize(texWidth, texHeight);
	transform->SetSize(texWidth, texHeight);
}

UI::TextureButton::~TextureButton()
{
	delete transform;
	delete texture;
	delete collider;
	delete collision;
}

void UI::TextureButton::Update()
{
	texture->Update();
}

void UI::TextureButton::Draw()
{
	texture->Draw();
	collider->Draw();
}