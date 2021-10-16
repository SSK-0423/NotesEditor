#pragma once
#include "Singleton.hpp"
#include "InputDevice.hpp"

/*
* キーボードの入力状態を検知するクラス
*/

namespace Engine
{
	namespace Input {

		class Keyboard : public Singleton<Keyboard>, public InputDevice {
			friend Singleton<Keyboard>;

		private:
			Keyboard() : InputDevice(KEY_NUM), keyPressingCount(), keyReleasingCount(), keyPressed() {}

			static constexpr int KEY_NUM = 256;
			int keyPressingCount[KEY_NUM];
			int keyReleasingCount[KEY_NUM];
			mutable bool keyPressed[KEY_NUM];
			
			void UpdateCounter();
			void UpdatePressingCounter(KeyCode keyCode);
			void UpdateReleasingCounter(KeyCode keyCode);
		public:
			void ReadInput() override;
			int GetPressingCount(KeyCode keyCode) const override;
			int GetReleasingCount(KeyCode keyCode) const override;
			bool IsPressKey(KeyCode keyCode) const override;
			bool IsReleaseKey(KeyCode keyCode) const override;
		};
	}
}