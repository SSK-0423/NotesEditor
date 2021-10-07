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
	class NotesEditorMusic;
	class MusicInfoTextBox : public Engine::UI::GUI {
	private:
		Engine::UI::TextureTextBox* textBox;
	public:
		MusicInfoTextBox(const char* filePath);
		~MusicInfoTextBox();
		void Update();
		void Draw();
		void UpdateText();
	};
}