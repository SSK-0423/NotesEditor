#include <DxLib.h>
#include "Mouse.hpp"

Mouse::Mouse() : buttonPressingCount(), buttonReleasingCount(), x(), y(),isLeftClicked(false),isRightClicked(false) {
}

//更新
bool Mouse::Update() 
{
	int nowButtonState = GetMouseInput();
	GetMousePoint(&x, &y);
	for (int i = 0; i < KEY_NUM; i++) 
	{
		//i番のボタンが押されていたら
		if ((nowButtonState >> i) & 1) 
		{            
			//離されカウンタが0より大きければ
			if (buttonReleasingCount[i] > 0) 
			{
				buttonReleasingCount[i] = 0;   //0に戻す
			}
			buttonPressingCount[i]++;          //押されカウンタを増やす
		}
		//i番のキーが離されていたら
		else 
		{                             
			//押されカウンタが0より大きければ
			if (buttonPressingCount[i] > 0) 
			{ 
				buttonPressingCount[i] = 0;    //0に戻す
			}
			buttonReleasingCount[i]++;         //離されカウンタを増やす
		}
	}
	return true;
}

//keyCodeのキーが押されているフレーム数を返す
int Mouse::GetPressingCount(int keyCode) 
{
	if (!IsAvailableCode(keyCode)) {
		return -1;
	}
	return buttonPressingCount[keyCode];
}

//keyCodeのキーが離されているフレーム数を返す
int Mouse::GetReleasingCount(int keyCode) 
{
	if (!IsAvailableCode(keyCode)) {
		return -1;
	}
	return buttonReleasingCount[keyCode];
}

//左クリックが押されたか
bool Mouse::IsLeftClick()
{
	if (GetPressingCount(Mouse::LEFT_CLICK) > 0) 
	{
		isLeftClicked = true;
		return true;
	}
	return false;
}

//右クリックが押されたか
bool Mouse::IsRightClick()
{
	if (GetPressingCount(Mouse::RIGHT_CLICK) > 0)
	{
		isRightClicked = true;
		return true;
	}
	return false;
}
//左クリックから指が離されたら
bool Mouse::IsLeftClickRelease()
{
	if (isLeftClicked && !IsLeftClick()) {
		isLeftClicked = false;
		return true;
	}
	return false;
}
//右クリックから指が離されたら
bool Mouse::IsRightClickRelease()
{
	if (isRightClicked && !IsRightClick()) {
		isRightClicked = false;
		return true;
	}
	return false;
}

//keyCodeが有効な値かチェックする
bool Mouse::IsAvailableCode(int keyCode) {
	if (!(0 <= keyCode && keyCode < KEY_NUM)) {
		return false;
	}
	return true;
}