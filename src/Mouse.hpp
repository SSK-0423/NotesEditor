#pragma once
#include "DxLib.h"
#include "GameSymbol.hpp"
#include "Singleton.hpp"
#include "InputDevice.hpp"
#include "Position.hpp"

namespace Game {

	namespace Input {

		class Mouse : public Singleton<Mouse>, public InputDevice{
			friend Singleton<Mouse>;

		private:
			Mouse() : InputDevice(KEY_NUM),buttonPressingCount(),buttonReleasingCount(),buttonPressed() {}

			// キー総数
			static constexpr int KEY_NUM = 8;

			// マウスポインタの座標
			mutable Component::Position mousePos;

			// 押されカウンタ
			mutable int buttonPressingCount[KEY_NUM];
			// 離されカウンタ
			mutable int buttonReleasingCount[KEY_NUM];
			// 押されたかどうか
			mutable bool buttonPressed[KEY_NUM];

			// カウンタ更新
			void UpdateCounter();
			void UpdatePressingCounter(KeyCode keyCode) const;
			void UpdateReleasingCounter(KeyCode keyCode) const;
			void GetMousePosition() const;
		public:
			static constexpr int LEFT_CLICK = 0;
			static constexpr int RIGHT_CLICK = 1;

			void ReadInput() override;
			// keyCodeのキーが押されているフレーム数を取得
			int GetPressingCount(KeyCode keyCode) const override;
			// keyCodeのキーが離されているフレーム数を取得
			int GetReleasingCount(KeyCode keyCode) const override;
			// キーが押されたか
			bool IsPressKey(KeyCode keyCode) const override;
			// キーから離されたか
			bool IsReleaseKey(KeyCode keyCode) const override;

			// マウスポインタの座標取得
			Component::Position GetPosition() const { return mousePos; }
			// マウスポインタのX座標取得
			float GetPosX() const { return mousePos.GetPosX(); }
			// マウスポインタのY座標取得
			float GetPosY() const { return mousePos.GetPosY(); }
		};
	}
}