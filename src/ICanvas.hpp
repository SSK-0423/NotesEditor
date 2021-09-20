#pragma once

namespace Game
{
	namespace Input
	{
		class InputDeviceContainer;
	}

	namespace Object
	{

		namespace UI
		{
			class ICanvas {
			public:
				virtual void Init() = 0;
				virtual void Update() = 0;
				virtual void Draw() = 0;
				virtual void Input(const Input::InputDeviceContainer&) = 0;
			};
		}
	}
}