#pragma once
#include "IInputDevice.hpp"
#include "Mouse.hpp"
#include "Keyboard.hpp"
#include "Singleton.hpp"
#include <vector>

/*
* ���̓f�o�C�X�̃C���X�^���X���擾���邽�߂̃N���X
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