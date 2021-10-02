#pragma once
#include "GameSymbol.hpp"
#include "GUI.hpp"
#include "Texture.hpp"
#include <string>
#include <vector>

namespace Engine
{
	namespace Components
	{
		class Texture;
	}
	namespace UI
	{
		class TextureTextBox : public GUI {
		private:
			// �t�H���g
			Font fontHandle;
			// �F
			Color color;
			// �e�L�X�g
			std::vector<std::string> text;
			// �e�L�X�g�{�b�N�X�̔w�i�摜
			Components::Texture* texture;

			void DrawStrings();
		public:
			TextureTextBox(const char* filePath);
			~TextureTextBox();
			void Update();
			void Draw();
			void AddText(std::string str);
			void SetColor(int r, int g, int b);
			void CreateFontHandle(const char* name, int size, int thick, int fonttype);
			void ResetText();
		};
	}
}