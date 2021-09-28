#include "InputDevice.hpp"

namespace Input {

	bool InputDevice::IsAvailableCode(KeyCode keyCode) const
	{
		if (0 <= keyCode && keyCode < KEY_NUM)
		{
			return true;
		}
		return false;
	}
}
