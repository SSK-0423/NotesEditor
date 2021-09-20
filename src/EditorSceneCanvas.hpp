#pragma once
#include "Canvas.hpp"

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
	public:
		EditorSceneCanvas();
		void Init();
		void Update();
		void Draw();
		void Input(const Game::Input::InputDeviceContainer&);
	};
}
