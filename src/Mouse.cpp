#include <DxLib.h>
#include "Mouse.hpp"

namespace Game {

	namespace Input {

		//更新
		void Mouse::ReadInput() const 
		{
			GetMousePoint(&mousePos.x, &mousePos.y);
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
			if (GetReleasingCount(keyCode) != 0 && buttonPressed[keyCode])
			{
				buttonPressed[keyCode] = false;
				return true;
			}
			return false;
		}

		void Mouse::UpdateCounter() const
		{
			int nowButtonState = GetMouseInput();

			for (int i = 0; i < KEY_NUM; i++) 
			{
				// i番のボタンが押されていたら
				if ((nowButtonState >> i) & 1) 
				{            
					// 離されカウンタが0より大きければ
					if (buttonReleasingCount[i] > 0) 
					{
						// 0に戻す
						buttonReleasingCount[i] = 0;   
					}
					// 押されカウンタを増やす
					buttonPressingCount[i]++;          
					buttonPressed[i] = true;
				}
				// i番のキーが離されていたら
				else 
				{                             
					// 押されカウンタが0より大きければ
					if (buttonPressingCount[i] > 0) 
					{ 
						// 0に戻す
						buttonPressingCount[i] = 0;    
					}
					// 離されカウンタを増やす
					buttonReleasingCount[i]++;         
				}
			}
		}
	}
}