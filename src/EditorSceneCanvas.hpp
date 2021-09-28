#pragma once
#include "Canvas.hpp"
#include "GUI.hpp"
#include "TestObject.h"
#include <vector>

namespace Input
{
	class InputDeviceContainer;
}
namespace NotesEditor
{
	class EditorSceneCanvas : public UI::Canvas
	{
	private:
		std::vector<UI::GUI> guiList;
		TestObject obj;
	public:
		EditorSceneCanvas();
		void Init();
		void Update();
		void Draw();
	};
}
