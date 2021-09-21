#pragma once
#include "TextureButton.hpp"

namespace Game 
{
	namespace Object 
	{
		namespace UI 
		{
			class TextureButtonRect : public TextureButton{
			private:
				 
			public:
				TextureButtonRect(const char* filePath);
				~TextureButtonRect();
				void Draw();
				void Input(const Game::Input::InputDeviceContainer& inputDeviceContainer);
			};
		}
	}
}