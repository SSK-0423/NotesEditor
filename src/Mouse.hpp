#pragma once
#include "DxLib.h"
#include "Singleton.hpp"

class Mouse : public Singleton<Mouse> {
	Mouse();//�R���X�g���N�^
	friend Singleton<Mouse>;

public:
	static constexpr int LEFT_CLICK = 0;
	static constexpr int RIGHT_CLICK = 1;

	bool Update();	//�X�V
	int GetPressingCount(int keyCode);//keyCode�̃L�[��������Ă���t���[�������擾
	int GetReleasingCount(int keyCode);//keyCode�̃L�[��������Ă���t���[�������擾
	bool IsLeftClick();
	bool IsRightClick();
	bool IsLeftClickRelease();
	bool IsRightClickRelease();
	int GetX() { return x; }
	int GetY() { return y; }
	Mouse* Get() { return this; }
private:
	static constexpr int KEY_NUM = 8;	//�L�[����
	int x, y;
	int buttonPressingCount[KEY_NUM];//������J�E���^
	int buttonReleasingCount[KEY_NUM];//������J�E���^

	bool isLeftClicked;
	bool isRightClicked;

	bool IsAvailableCode(int keyCode);//keyCode���L���ȃL�[�ԍ����₤

};
