#include <DxLib.h>
#include "Mouse.hpp"

Mouse::Mouse() : buttonPressingCount(), buttonReleasingCount(), x(), y() {
}

//�X�V
bool Mouse::Update() {
	int nowButtonState = GetMouseInput();
	GetMousePoint(&x, &y);
	for (int i = 0; i < KEY_NUM; i++) {
		if ((nowButtonState >> i) & 1) {            //i�Ԃ̃{�^����������Ă�����
			if (buttonReleasingCount[i] > 0) {//������J�E���^��0���傫�����
				buttonReleasingCount[i] = 0;   //0�ɖ߂�
			}
			buttonPressingCount[i]++;          //������J�E���^�𑝂₷
		}
		else {                             //i�Ԃ̃L�[��������Ă�����
			if (buttonPressingCount[i] > 0) { //������J�E���^��0���傫�����
				buttonPressingCount[i] = 0;    //0�ɖ߂�
			}
			buttonReleasingCount[i]++;         //������J�E���^�𑝂₷
		}
	}
	return true;
}

//keyCode�̃L�[��������Ă���t���[������Ԃ�
int Mouse::GetPressingCount(int keyCode) {
	if (!IsAvailableCode(keyCode)) {
		return -1;
	}
	return buttonPressingCount[keyCode];
}

//keyCode�̃L�[��������Ă���t���[������Ԃ�
int Mouse::GetReleasingCount(int keyCode) {
	if (!IsAvailableCode(keyCode)) {
		return -1;
	}
	return buttonReleasingCount[keyCode];
}

//keyCode���L���Ȓl���`�F�b�N����
bool Mouse::IsAvailableCode(int keyCode) {
	if (!(0 <= keyCode && keyCode < KEY_NUM)) {
		return false;
	}
	return true;
}