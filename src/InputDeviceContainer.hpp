#pragma once
#include "IInputDevice.hpp"
#include "Mouse.hpp"
#include "Keyboard.hpp"
#include "Singleton.hpp"
#include <vector>

namespace Game {

	namespace Input {

		class InputDeviceContainer : public Singleton<InputDeviceContainer> {
		public:
			// キーボードのインスタンス取得
			Keyboard& GetKeyboard() const
			{
				return Keyboard::Instance();
			}
			// マウスのインスタンス取得
			Mouse& GetMouse() const
			{
				return Mouse::Instance();
			}
		};
	}
}