#pragma once
#include "Singleton.hpp"
#include "InputDevice.hpp"

namespace Game {
	
	namespace Input {

		class Keyboard : public Singleton<Keyboard>, public InputDevice{
			friend Singleton<Keyboard>;
		private:
			Keyboard() : InputDevice(KEY_NUM), keyPressingCount(), keyReleasingCount(),keyPressed() {}
	
			// キーの総数
			static constexpr int KEY_NUM = 256;
			// 押されカウンタ
			mutable int keyPressingCount[KEY_NUM];
			// 離されカウンタ
			mutable int keyReleasingCount[KEY_NUM];
			// 押されたかどうか
			mutable bool keyPressed[KEY_NUM];
			// カウンタ更新
			void UpdateCounter() const;
		public:
			void ReadInput() const override;
			int GetPressingCount(KeyCode keyCode) const override;
			int GetReleasingCount(KeyCode keyCode) const override;
			bool IsPressKey(KeyCode keyCode) const override;
			bool IsReleaseKey(KeyCode keyCode) const override;
		};
	}
}