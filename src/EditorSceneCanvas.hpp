#pragma once
#include "Canvas.hpp"
#include "TestObject.h"

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
		TestObject obj;
	public:
		EditorSceneCanvas();
		void Init();
		void Update();
		void Draw();
	};
}
