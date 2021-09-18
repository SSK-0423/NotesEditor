#pragma once
#include "DxLib.h"
#include "Game.hpp"
#include "Singleton.hpp"
#include "InputDevice.hpp"

namespace Game {

	namespace Input {

		class Mouse : public Singleton<Mouse>, public InputDevice{
			friend Singleton<Mouse>;

		private:
			Mouse() : InputDevice(KEY_NUM),buttonPressingCount(),buttonReleasingCount(),buttonPressed() {}

			// キー総数
			static constexpr int KEY_NUM = 8;

			// マウスポインタの座標
			mutable Position2D<int> mousePos;

			// 押されカウンタ
			mutable int buttonPressingCount[KEY_NUM];
			// 離されカウンタ
			mutable int buttonReleasingCount[KEY_NUM];
			// 押されたかどうか
			mutable bool buttonPressed[KEY_NUM];
			// カウンタ更新
			void UpdateCounter() const;

		public:
			static constexpr int LEFT_CLICK = 0;
			static constexpr int RIGHT_CLICK = 1;

			// 更新
			void ReadInput() const override;
			// keyCodeのキーが押されているフレーム数を取得
			int GetPressingCount(KeyCode keyCode) const override;
			// keyCodeのキーが離されているフレーム数を取得
			int GetReleasingCount(KeyCode keyCode) const override;
			// キーが押されたか
			bool IsPressKey(KeyCode keyCode) const override;
			// キーから離されたか
			bool IsReleaseKey(KeyCode keyCoce) const override;

			// マウスポインタの座標取得
			Position2D<int> GetPosition() const { return mousePos; }
			// マウスポインタのX座標取得
			int GetPosX() const { return mousePos.x; }
			// マウスポインタのY座標取得
			int GetPosY() const { return mousePos.y; }
		};
	}
}