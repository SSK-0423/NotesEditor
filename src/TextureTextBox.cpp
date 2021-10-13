#include "TextureTextBox.hpp"
#include "Transform.hpp"
#include "DxLib.h"

void Engine::UI::TextureTextBox::DrawStrings()
{
	Engine::Components::Position pos = transform->GetPosition();
	Engine::Components::Size size = transform->GetSize();

	for (size_t i = 0; i < text.size(); i++)
	{
		int stringWidth = GetDrawStringWidthToHandle(text[i].c_str(), text[i].size(), fontHandle);
		//if (stringWidth >= 13 * 19 && i == 0)
		//{
		//	DrawFormatString(700, 700, GetColor(0, 255, 0), "•¶Žš•:%d", stringWidth);
		//	fontHandle = CreateFontToHandle("default", stringWidth / text[i].size(), 1, DX_FONTTYPE_ANTIALIASING);
		//}
		DrawFormatStringToHandle(pos.x - stringWidth / 2.f,
			pos.y - size.height / 2 + size.height / text.size() * (i + 1) - 37.5,
			color, fontHandle, text[i].c_str());
	}
}

Engine::UI::TextureTextBox::TextureTextBox(const char* filePath) : color(GetColor(255, 255, 255))
{
	fontHandle = CreateFontToHandle("default", 25, 1, DX_FONTTYPE_ANTIALIASING);
	transform = new Engine::Components::Transform();
	texture = new Engine::Components::Texture(*transform, filePath);
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
}

void Engine::UI::TextureTextBox::AddText(std::string str)
{
	text.push_back(str);
}

void Engine::UI::TextureTextBox::SetColor(int r, int g, int b)
{
	color = GetColor(r, g, b);
}

void Engine::UI::TextureTextBox::CreateFontHandle(const char* name, int size, int thick, int fonttype)
{
	fontHandle = CreateFontToHandle(name, size, thick, fonttype);
}

void Engine::UI::TextureTextBox::ResetText()
{
	text.clear();
	text.shrink_to_fit();
}
