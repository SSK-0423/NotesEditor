#include "InputDevice.hpp"

bool Engine::Input::InputDevice::IsAvailableCode(KeyCode keyCode) const
{
	return 0 <= keyCode && keyCode < KEY_NUM;
}
