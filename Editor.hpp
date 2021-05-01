#pragma once
#include "BaseScene.hpp"
#include "Button.hpp"
#include "Camera2D.hpp"
#include "TextBox.hpp"
#include "BarManager.hpp"

#define BUTTON_SIZE_WIDTH 126
#define BUTTON_SIZE_HEIGHT 66
#define BUTTON_SIZE2_HEIGHT 66
#define ADD 10
#define BUTTON_POS_Y BUTTON_SIZE_HEIGHT*2 + ADD*4

typedef enum BUTTON {
	BUTTON_SHORT,		// �V���[�g�m�[�c��z�u����{�^��
	BUTTON_LONG,		// �����O�m�[�c��z�u����{�^��
	BUTTON_SLIDE,		// �X���C�h�m�[�c��z�u����{�^��
	BUTTON_PLAY,		// �Ȃ̍Đ���~�{�^��
	BUTTON_RESTART,		// �Ȃ��͂��߂���Đ�����{�^��
	BUTTON_CHANGEBAR,	// ���ߐ���1/1�ɕύX����{�^��
	BUTTON_CHANGEBAR4,	// ���ߐ���1/4�ɕύX����{�^��
	BUTTON_CHANGEBAR8,	// ���ߐ���1/8�ɕύX����{�^��
	BUTTON_CHANGEBAR16,	// ���ߐ���1/16�ɕύX����{�^��
	BUTTON_CHANGEBAR32,	// ���ߐ���1/32�ɕύX����{�^��
	BUTTON_LOADMUSIC,	// �Ȃ�ǂݍ��ރ{�^��
	BUTTON_LOAD,		// �쐬�������ʂ̓ǂݍ���
	BUTTON_SAVE,		// �쐬�������ʂ̕ۑ�
	BUTTON_NUM			// �{�^���̐�
};

//�G�f�B�^�[��ʃN���X
class Editor :public BaseScene {
private:
	int fontHandle;			//�y�ȏ��\���̃t�H���g
	int speed;				//�X�N���[���X�s�[�h
	int backgroungHandle;	//�w�i
	int laneHandle;			//���[��	
	//int lineHandle;			//�m�[�c���C��

	//���ߐ��̃n���h��
	int barHandle;		// 1/1
	int bar4Handle;		// 1/4
	int bar8Handle;		// 1/8
	int bar16Handle;	// 1/16
	int bar32Handle;	// 1/32

	int musicInfoHandle;	//�y�ȏ��\���g

	int count; // �Ȃ��Đ����Ă���o�߂����t���[����

	Button* button;
	TextBox text;
	Music music;
	Camera2D camera;
	BarManager barManager;

	// ���ߐ��̕`��
	// �y�Ȃ�BPM�ƍĐ����Ԃ��珬�ߐ����Z�o���ĕ`��
	void MakeBar();
	void DrawButton();
	void InitButton();
	void DebugDraw();

public:
	Editor(ISceneChanger* changer);
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};