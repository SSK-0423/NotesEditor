#pragma once
#include "InputDeviceContainer.hpp"

namespace Game {

	class IScene {
	public:
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void Input(const Input::InputDeviceContainer& inputDeviceContainer) = 0;
	};
}