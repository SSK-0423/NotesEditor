#include "TextureButton.hpp"
#include "Transform.hpp"
#include "Texture.hpp"

Game::Object::UI::TextureButton::TextureButton(const char* filePath)
{
	transform = new Component::Transform();
	texture = new Component::Texture(*transform,filePath);
}

Game::Object::UI::TextureButton::~TextureButton()
{
	delete transform;
	delete texture;
}

void Game::Object::UI::TextureButton::Draw()
{
	texture->Draw();
}
