#pragma once
#include "GUI.hpp"

namespace Engine
{
	namespace UI
	{
		class TextureTextBox;
	}
}

namespace NotesEditor
{
	class MusicInfoTextBox : public Engine::UI::GUI{
	private:
		Engine::UI::TextureTextBox* textBox;
		void UpdateText();
	public:
		MusicInfoTextBox(const char* filePath);
		~MusicInfoTextBox();
		void Update();
		void Draw();
	};
}