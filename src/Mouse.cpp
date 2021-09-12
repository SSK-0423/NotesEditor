#include <DxLib.h>
#include "Mouse.hpp"

Mouse::Mouse() : buttonPressingCount(), buttonReleasingCount(), x(), y(),isLeftClicked(false),isRightClicked(false) {
}

//�X�V
bool Mouse::Update() 
{
	int nowButtonState = GetMouseInput();
	GetMousePoint(&x, &y);
	for (int i = 0; i < KEY_NUM; i++) 
	{
		//i�Ԃ̃{�^����������Ă�����
		if ((nowButtonState >> i) & 1) 
		{            
			//������J�E���^��0���傫�����
			if (buttonReleasingCount[i] > 0) 
			{
				buttonReleasingCount[i] = 0;   //0�ɖ߂�
			}
			buttonPressingCount[i]++;          //������J�E���^�𑝂₷
		}
		//i�Ԃ̃L�[��������Ă�����
		else 
		{                             
			//������J�E���^��0���傫�����
			if (buttonPressingCount[i] > 0) 
			{ 
				buttonPressingCount[i] = 0;    //0�ɖ߂�
			}
			buttonReleasingCount[i]++;         //������J�E���^�𑝂₷
		}
	}
	return true;
}

//keyCode�̃L�[��������Ă���t���[������Ԃ�
int Mouse::GetPressingCount(int keyCode) 
{
	if (!IsAvailableCode(keyCode)) {
		return -1;
	}
	return buttonPressingCount[keyCode];
}

//keyCode�̃L�[��������Ă���t���[������Ԃ�
int Mouse::GetReleasingCount(int keyCode) 
{
	if (!IsAvailableCode(keyCode)) {
		return -1;
	}
	return buttonReleasingCount[keyCode];
}

//���N���b�N�������ꂽ��
bool Mouse::IsLeftClick()
{
	if (GetPressingCount(Mouse::LEFT_CLICK) > 0) 
	{
		isLeftClicked = true;
		return true;
	}
	return false;
}

//�E�N���b�N�������ꂽ��
bool Mouse::IsRightClick()
{
	if (GetPressingCount(Mouse::RIGHT_CLICK) > 0)
	{
		isRightClicked = true;
		return true;
	}
	return false;
}
//���N���b�N����w�������ꂽ��
bool Mouse::IsLeftClickRelease()
{
	if (isLeftClicked && !IsLeftClick()) {
		isLeftClicked = false;
		return true;
	}
	return false;
}
//�E�N���b�N����w�������ꂽ��
bool Mouse::IsRightClickRelease()
{
	if (isRightClicked && !IsRightClick()) {
		isRightClicked = false;
		return true;
	}
	return false;
}

//keyCode���L���Ȓl���`�F�b�N����
bool Mouse::IsAvailableCode(int keyCode) {
	if (!(0 <= keyCode && keyCode < KEY_NUM)) {
		return false;
	}
	return true;
}