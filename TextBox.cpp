#include "TextBox.hpp"
#include "DxLib.h"

TextBox::TextBox() {
	position.x = BOX_SIZE_WIDTH / 2 + 8;
	position.y = BOX_SIZE_HEIGHT / 2 + 8;
	width = BOX_SIZE_WIDTH;
	height = BOX_SIZE_HEIGHT;
	fontHandle = CreateFontToHandle("default", 25, 1, DX_FONTTYPE_ANTIALIASING);
	imageHandle = -1;
	color = GetColor(255, 255, 255);
}
TextBox::~TextBox() {

}
void TextBox::Update() {

}

void TextBox::Draw() {
	DrawModiGraph(
		position.x - width / 2, position.y - height / 2, //左上座標
		position.x + width / 2, position.y - height / 2, //右上座標
		position.x + width / 2, position.y + height / 2, //右下座標
		position.x - width / 2, position.y + height / 2, //左下座標
		imageHandle, true); //グラフィックハンドル、透過処理
	DrawFormatString(0, 100, color, "%d", text.size());
	for (int i = 0; i < text.size(); i++) {
		DrawFormatStringToHandle(position.x - GetDrawStringWidthToHandle(text[i].c_str(), text[i].size(), fontHandle) / 2, position.y - height / 2 + height / text.size() * (i+1) - 37.5, color, fontHandle, text[i].c_str());
	}
	text.clear();
}
void TextBox::SetText(const char* str) {
	std::string s = str;
	text.push_back(str);
	//for (int i = 0; i < s.size(); i++) {
	//	std::string s2;
	//	DrawFormatString(0, 200, color, "%d", i);
	//	if (s[i] != '\n' || s[i] != '\0') {
	//		s2 += s[i];
	//	}
	//	else if (s[i] == '\n') {
	//		text.push_back(s2);
	//		//s2.clear();
	//	}
	//	else if (s[i] == '\0') {
	//		text.push_back(s2);
	//		//s2.clear();
	//		break;
	//	}
	//}
}
void TextBox::SetColor(int r, int g, int b) {
	color = GetColor(r, g, b);
}
void TextBox::CreateFontHandle(const char* name, int size, int thick, int fonttype) {
	fontHandle = CreateFontToHandle(name, size, thick, fonttype);
}
void TextBox::SetImage(int handle) {
	imageHandle = handle;
}