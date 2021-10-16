#pragma once

/*
* 入力デバイスのインターフェース
*/

namespace Engine
{
	namespace Input {

		using KeyCode = int;
		class IInputDevice {
		public:
			virtual ~IInputDevice() {}
			virtual void ReadInput() = 0;
			virtual int GetPressingCount(KeyCode keyCode) const = 0;
			virtual int GetReleasingCount(KeyCode keyCode) const = 0;
			virtual bool IsPressKey(KeyCode keyCode) const = 0;
			virtual bool IsReleaseKey(KeyCode keyCode) const = 0;
		};

	}
}
