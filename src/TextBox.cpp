#include "TextBox.hpp"
#include "DxLib.h"

void TextBox::DrawStrings()
{
	Position2D<float> textBoxPos = transform.GetPosition();
	Size2D<float> textBoxSize = transform.GetSize();
	for (int i = 0; i < text.size(); i++) 
	{
		DrawFormatStringToHandle(textBoxPos.x - 
			GetDrawStringWidthToHandle(text[i].c_str(), text[i].size(), fontHandle) / 2.f, textBoxPos.y - textBoxSize.height / 2 + textBoxSize.height / text.size() * (i+1) - 37.5, 
			color, fontHandle, text[i].c_str());
	}
	text.clear();
}

TextBox::TextBox() noexcept
{
	this->transform.SetPosition({ BOX_SIZE_WIDTH / 2.f + 8,BOX_SIZE_HEIGHT / 2.f + 8 });
	this->transform.SetSize({ BOX_SIZE_WIDTH * 1.f,BOX_SIZE_HEIGHT * 1.f });
	fontHandle = CreateFontToHandle("default", 25, 1, DX_FONTTYPE_ANTIALIASING);
	color = GetColor(255, 255, 255);
	texture = new Texture(this->transform);
}

TextBox::~TextBox() noexcept 
{

}
void TextBox::Update() noexcept 
{

}

void TextBox::Draw() noexcept 
{
	texture->Draw();
	DrawStrings();
	DrawFormatString(0, 100, color, "%d", text.size());
}

// テキスト追加
void TextBox::AddText(std::string str) noexcept 
{
	std::string s = str;
	text.push_back(str);
}
// 色セット
void TextBox::SetColor(int r, int g, int b) noexcept 
{
	color = GetColor(r, g, b);
}
// フォントハンドルの生成
void TextBox::CreateFontHandle(const char* name, int size, int thick, int fonttype) noexcept 
{
	fontHandle = CreateFontToHandle(name, size, thick, fonttype);
}

const Texture& TextBox::GetTexture()
{
	return *texture;
}
