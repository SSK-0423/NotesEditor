#include <DxLib.h>
#include "Mouse.hpp"

namespace Game {

	namespace Input {

		//更新
		void Mouse::ReadInput() const 
		{
			GetMousePosition();
			UpdateCounter();
		}

		//keyCodeのキーが押されているフレーム数を返す
		int Mouse::GetPressingCount(KeyCode keyCode) const
		{
			if (IsAvailableCode(keyCode)) 
				return buttonPressingCount[keyCode];
			return -1;
		}

		//keyCodeのキーが離されているフレーム数を返す
		int Mouse::GetReleasingCount(KeyCode keyCode) const
		{
			if (IsAvailableCode(keyCode)) 
				return buttonReleasingCount[keyCode];
			return -1;
		}

		bool Mouse::IsPressKey(KeyCode keyCode) const
		{
			if (GetPressingCount(keyCode) == 1)
				return true;
			return false;
		}

		bool Mouse::IsReleaseKey(KeyCode keyCode) const
		{
			if (GetPressingCount(keyCode) == 0 && buttonPressed[keyCode])
			{
				buttonPressed[keyCode] = false;
				return true;
			}
			return false;
		}

		void Mouse::UpdateCounter() const
		{
			KeyCode nowButtonState = GetMouseInput();

			for (KeyCode keyCode = 0; keyCode < KEY_NUM; keyCode++) 
			{
				// i番のボタンが押されていたら
				if ((nowButtonState >> keyCode) & 1)
					UpdatePressingCounter(keyCode);
				// i番のキーが離されていたら
				else
					UpdateReleasingCounter(keyCode);
			}
		}

		void Mouse::UpdatePressingCounter(KeyCode keyCode) const
		{
			// 離されカウンタが0より大きければ
			if (buttonReleasingCount[keyCode] > 0)
			{
				// 0に戻す
				buttonReleasingCount[keyCode] = 0;
			}
			// 押されカウンタを増やす
			buttonPressingCount[keyCode]++;
			buttonPressed[keyCode] = true;
		}

		void Mouse::UpdateReleasingCounter(KeyCode keyCode) const
		{
			// 押されカウンタが0より大きければ
			if (buttonPressingCount[keyCode] > 0) 
			{ 
				// 0に戻す
				buttonPressingCount[keyCode] = 0;
			}
			// 離されカウンタを増やす
			buttonReleasingCount[keyCode]++;
		}
		void Mouse::GetMousePosition() const
		{
			int x, y;
			GetMousePoint(&x,&y);
			mousePos.SetPosition(static_cast<float>(x), static_cast<float>(y));
		}
	}
}