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
			// フォント
			Font fontHandle;
			// 色
			Color color;
			// テキスト
			std::vector<std::string> text;
			// テキストボックスの背景画像
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