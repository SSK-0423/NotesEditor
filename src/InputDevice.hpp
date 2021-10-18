#pragma once
#include "IInputDevice.hpp"

/*
* 入力デバイス
*/

namespace Engine
{
	namespace Input
	{

		class InputDevice : public IInputDevice {
		private:
			const int KEY_NUM;
		protected:
			bool IsAvailableCode(KeyCode keyCode) const;
		public:
			InputDevice(int num) : KEY_NUM(num) {}
			virtual ~InputDevice() {}
		};
	}
}
