#include "TextureTextBox.hpp"
#include "Transform.hpp"
#include "DxLib.h"

void Engine::UI::TextureTextBox::DrawStrings()
{
	//Position2D<float> textBoxPos = transform.GetPosition();
	//Size2D<float> textBoxSize = transform.GetSize();
	transform->GetPosition();
	transform->GetRotation();

	//for (int i = 0; i < text.size(); i++) 
	//{
	//	DrawFormatStringToHandle(textBoxPos.x - 
	//		GetDrawStringWidthToHandle(text[i].c_str(), text[i].size(), fontHandle) / 2.f, textBoxPos.y - textBoxSize.height / 2 + textBoxSize.height / text.size() * (i+1) - 37.5, 
	//		color, fontHandle, text[i].c_str());
	//}
	//text.clear();
}

Engine::UI::TextureTextBox::TextureTextBox(const char* filePath)
{
	transform = new Engine::Components::Transform();
	//this->transform.SetPosition({ BOX_SIZE_WIDTH / 2.f + 8,BOX_SIZE_HEIGHT / 2.f + 8 });
	//this->transform.SetSize({ BOX_SIZE_WIDTH * 1.f,BOX_SIZE_HEIGHT * 1.f });

	fontHandle = CreateFontToHandle("default", 25, 1, DX_FONTTYPE_ANTIALIASING);
	color = GetColor(255, 255, 255);
	texture = new Engine::Components::Texture(*transform,filePath);
}

Engine::UI::TextureTextBox::~TextureTextBox()
{

}
void Engine::UI::TextureTextBox::Update()
{
	texture->Update();
}

void Engine::UI::TextureTextBox::Draw()
{
	texture->Draw();
	DrawStrings();
	DrawFormatString(0, 100, color, "%d", text.size());
}

// テキスト追加
void Engine::UI::TextureTextBox::AddText(std::string str)
{
	std::string s = str;
	text.push_back(str);
}
// 色セット
void Engine::UI::TextureTextBox::SetColor(int r, int g, int b)
{
	color = GetColor(r, g, b);
}
// フォントハンドルの生成
void Engine::UI::TextureTextBox::CreateFontHandle(const char* name, int size, int thick, int fonttype)
{
	fontHandle = CreateFontToHandle(name, size, thick, fonttype);
}
