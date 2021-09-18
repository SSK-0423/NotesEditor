#pragma once
#include "Game.hpp"
#include "GUI.hpp"
#include "Texture.hpp"
#include <string>
#include <vector>
#define BOX_SIZE_WIDTH 252
#define BOX_SIZE_HEIGHT 122

class TextBox : public GUI{
private:
	// �t�H���g
	Font fontHandle;
	// �F
	Color color;
	// �e�L�X�g
	std::vector<std::string> text;
	// �e�L�X�g�{�b�N�X�̔w�i�摜
	Texture* texture;

	void DrawStrings();
public:
	TextBox() noexcept;
	~TextBox() noexcept;
	void Update() noexcept;
	void Draw() noexcept;
	void AddText(std::string str) noexcept;
	void SetColor(int r, int g, int b) noexcept;
	void CreateFontHandle(const char* name, int size, int thick, int fonttype) noexcept;
	const Texture& GetTexture();
};