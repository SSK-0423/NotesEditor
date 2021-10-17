#pragma once
#include "GameUtility.hpp"
#include "Singleton.hpp"
#include "InputDevice.hpp"
#include "Position.hpp"

/*
* マウスの入力状態を検知するクラス
*/

namespace Engine
{
	namespace Input {

		class Mouse : public Singleton<Mouse>, public InputDevice {
			friend Singleton<Mouse>;

		private:
			Mouse() : InputDevice(KEY_NUM), buttonPressingCount(), buttonReleasingCount(), buttonPressed() {}

			static constexpr int KEY_NUM = 8;
			mutable Components::Position mousePos;
			int buttonPressingCount[KEY_NUM];
			int buttonReleasingCount[KEY_NUM];
			mutable bool buttonPressed[KEY_NUM];
			int mouseWheelRotVol;
			void UpdateCounter();
			void UpdatePressingCounter(KeyCode keyCode);
			void UpdateReleasingCounter(KeyCode keyCode);
			void UpdateMousePosition() const;
			void UpdateMouseWheelRotVol();
		public:
			static constexpr int LEFT_CLICK = 0;
			static constexpr int RIGHT_CLICK = 1;

			void ReadInput() override;
			int GetPressingCount(KeyCode keyCode) const override;
			int GetReleasingCount(KeyCode keyCode) const override;
			bool IsPressKey(KeyCode keyCode) const override;
			bool IsReleaseKey(KeyCode keyCode) const override;
			int GetMouseWheelRotVol() const;

			Components::Position GetPosition() const { return mousePos; }
			float GetPosX() const { return mousePos.x; }
			float GetPosY() const { return mousePos.y; }
		};
	}
}
