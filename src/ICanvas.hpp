#pragma once

namespace Input
{
	class InputDeviceContainer;
}

namespace UI
{
	class ICanvas {
	public:
		virtual void Update() = 0;
		virtual void Draw() = 0;
	};
}