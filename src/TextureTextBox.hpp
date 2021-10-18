#pragma once
#include "GameUtility.hpp"
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
			std::vector<std::string> text;
			Components::Texture* texture;
			Font fontHandle;
			Color color;
			static const int FONTSIZE;
			static const int FONTTHICK;
			void DrawStrings();
		public:
			TextureTextBox(const char* filePath);
			~TextureTextBox();
			void Update() override;
			void Draw() override;
			void AddText(std::string str);
			void SetColor(Color color);
			void CreateFontHandle(const char* name, int size, int thick, int fonttype);
			void ResetText();
		};
	}
}