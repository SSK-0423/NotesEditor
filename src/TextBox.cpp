#include "TextBox.hpp"
#include "DxLib.h"

TextBox::TextBox() noexcept {
	position.x = BOX_SIZE_WIDTH / 2 + 8;
	position.y = BOX_SIZE_HEIGHT / 2 + 8;
	width = BOX_SIZE_WIDTH;
	height = BOX_SIZE_HEIGHT;
	fontHandle = CreateFontToHandle("default", 25, 1, DX_FONTTYPE_ANTIALIASING);
	imageHandle = -1;
	color = GetColor(255, 255, 255);
}
TextBox::~TextBox() noexcept {

}
void TextBox::Update() noexcept {

}

void TextBox::Draw() noexcept {
	DrawModiGraph(
		position.x - width / 2, position.y - height / 2, //������W
		position.x + width / 2, position.y - height / 2, //�E����W
		position.x + width / 2, position.y + height / 2, //�E�����W
		position.x - width / 2, position.y + height / 2, //�������W
		imageHandle, true); //�O���t�B�b�N�n���h���A���ߏ���
	DrawFormatString(0, 100, color, "%d", text.size());
	for (int i = 0; i < text.size(); i++) {
		DrawFormatStringToHandle(position.x - GetDrawStringWidthToHandle(text[i].c_str(), text[i].size(), fontHandle) / 2, position.y - height / 2 + height / text.size() * (i+1) - 37.5, color, fontHandle, text[i].c_str());
	}
	text.clear();
}
void TextBox::SetText(std::string str) noexcept {
	std::string s = str;
	text.push_back(str);
}
void TextBox::SetColor(int r, int g, int b) noexcept {
	color = GetColor(r, g, b);
}
void TextBox::CreateFontHandle(const char* name, int size, int thick, int fonttype) noexcept {
	fontHandle = CreateFontToHandle(name, size, thick, fonttype);
}