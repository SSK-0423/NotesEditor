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
			// �L�[�{�[�h�̃C���X�^���X�擾
			Keyboard& GetKeyboard() const
			{
				return Keyboard::Instance();
			}
			// �}�E�X�̃C���X�^���X�擾
			Mouse& GetMouse() const
			{
				return Mouse::Instance();
			}
		};
	}
}