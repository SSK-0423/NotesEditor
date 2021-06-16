#include <DxLib.h>
#include "Mouse.hpp"

Mouse::Mouse() : buttonPressingCount(), buttonReleasingCount(), x(), y() {
}

//更新
bool Mouse::Update() {
	int nowButtonState = GetMouseInput();
	GetMousePoint(&x, &y);
	for (int i = 0; i < KEY_NUM; i++) {
		if ((nowButtonState >> i) & 1) {            //i番のボタンが押されていたら
			if (buttonReleasingCount[i] > 0) {//離されカウンタが0より大きければ
				buttonReleasingCount[i] = 0;   //0に戻す
			}
			buttonPressingCount[i]++;          //押されカウンタを増やす
		}
		else {                             //i番のキーが離されていたら
			if (buttonPressingCount[i] > 0) { //押されカウンタが0より大きければ
				buttonPressingCount[i] = 0;    //0に戻す
			}
			buttonReleasingCount[i]++;         //離されカウンタを増やす
		}
	}
	return true;
}

//keyCodeのキーが押されているフレーム数を返す
int Mouse::GetPressingCount(int keyCode) {
	if (!IsAvailableCode(keyCode)) {
		return -1;
	}
	return buttonPressingCount[keyCode];
}

//keyCodeのキーが離されているフレーム数を返す
int Mouse::GetReleasingCount(int keyCode) {
	if (!IsAvailableCode(keyCode)) {
		return -1;
	}
	return buttonReleasingCount[keyCode];
}

//keyCodeが有効な値かチェックする
bool Mouse::IsAvailableCode(int keyCode) {
	if (!(0 <= keyCode && keyCode < KEY_NUM)) {
		return false;
	}
	return true;
}