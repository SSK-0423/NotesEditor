#pragma once
#include "Canvas.hpp"
#include "GUI.hpp"
#include "TestObject.h"
#include <vector>

namespace NotesEditor
{
	class EditorSceneCanvas : public Engine::UI::Canvas
	{
	private:
		std::vector<Engine::UI::GUI> guiList;
		TestObject obj;
	public:
		EditorSceneCanvas();
		void Init();
		void Update();
		void Draw();
	};
}
