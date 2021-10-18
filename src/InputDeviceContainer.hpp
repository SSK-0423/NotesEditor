#pragma once
#include "IInputDevice.hpp"
#include "Mouse.hpp"
#include "Keyboard.hpp"
#include "Singleton.hpp"
#include <vector>

/*
* 入力デバイスのインスタンスを取得するためのクラス
*/

namespace Engine
{
	namespace Input {

		class InputDeviceContainer : public Singleton<InputDeviceContainer> {
			friend Singleton<InputDeviceContainer>;
		private:
			InputDeviceContainer() {}

		public:
			const Keyboard& GetKeyboard() const
			{
				return Keyboard::Instance();
			}
			const Mouse& GetMouse() const
			{
				return Mouse::Instance();
			}
		};
	}
}