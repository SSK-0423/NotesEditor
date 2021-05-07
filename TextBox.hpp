#pragma once
#include "GameObject.hpp"
#include <string>
#include <vector>
#define BOX_SIZE_WIDTH 252
#define BOX_SIZE_HEIGHT 122

class TextBox : public GameObject{
private:
	//フォント
	int fontHandle;
	//色
	unsigned int color;
	
	//テキスト
	std::vector<std::string> text;
public:
	TextBox() noexcept;
	~TextBox() noexcept;
	void Update() noexcept;
	void Draw() noexcept;
	void SetText(std::string str) noexcept;
	void SetColor(int r, int g, int b) noexcept;
	void CreateFontHandle(const char* name, int size, int thick, int fonttype) noexcept;
};