#pragma once
#include "BaseScene.hpp"
#include "Button.hpp"
#include "Camera2D.hpp"
#include "TextBox.hpp"
#include "BarManager.hpp"
#include "NotesManager.hpp"
#include <vector>

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

	int musicInfoHandle;	//�y�ȏ��\���g

	int count; // �Ȃ��Đ����Ă���o�߂����t���[����

	float frame_move; //�����X�N���[������1�t���[��������̃J�����̈ړ���

	Button* button;
	TextBox text;
	Music music;
	Camera2D camera;
	BarManager barManager;
	NotesManager notesManager;

	//�G�f�B�^�[���̑S�ẴI�u�W�F�N�g
	std::vector<GameObject*> objList;

	// ���ߐ��̕`��
	// �y�Ȃ�BPM�ƍĐ����Ԃ��珬�ߐ����Z�o���ĕ`��
	void MakeBar() noexcept;
	//�{�^���̍X�V
	void UpdateButton() noexcept;
	// �{�^���`��
	void DrawButton() noexcept;
	// �e�L�X�g�{�b�N�X�`��
	//void DrawTextBox() noexcept;
	//�{�^���̏�����
	void InitButton() noexcept;
	//�e�L�X�g�{�b�N�X�̏�����
	void InitTextBox() noexcept;
	//�{�^���̉摜�Z�b�g
	void SetButtonImage() noexcept;
	//�{�^���̈ʒu�Z�b�g
	void SetButtonPos() noexcept;
	//�{�^���̃C�x���g�֐��Z�b�g
	void SetClickEventFunc() noexcept;
	//���ߐ��Ǘ��N���X�̏�����
	void InitBarManager() noexcept;
	//�J�����X�N���[��
	void ScrollCamera() noexcept;
	//�L�[���͊Ǘ�
	void KeyInput() noexcept;
	//�f�o�b�O�p�e�L�X�g�Ȃǂ̕`��
	void DebugDraw() noexcept;
	//�����X�N���[�����̈ړ����v�Z
	void CalcFrameMove() noexcept;
	//�m�[�c�̐ݒu
	void PutNotes() noexcept;
	//�I�u�W�F�N�g�̔j��
	void DeleteObj() noexcept;

public:
	Editor(ISceneChanger* changer);
	void Initialize()  noexcept override;
	void Finalize()  noexcept override;
	void Update()  noexcept override;
	void Draw()  noexcept override;
	void AddObject(GameObject& obj) noexcept;
};