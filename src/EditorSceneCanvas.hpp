#pragma once
#include "Canvas.hpp"
#include "GUI.hpp"
#include "TestObject.h"
#include <vector>

namespace Game
{
	namespace Input
	{
		class InputDeviceContainer;
	}
}
namespace NotesEditor 
{
	class EditorSceneCanvas : public Game::Object::UI::Canvas
	{
	private:
		std::vector<Game::Object::UI::GUI> guiList;
		TestObject obj;
	public:
		EditorSceneCanvas();
		void Init();
		void Update();
		void Draw();
	};
}
