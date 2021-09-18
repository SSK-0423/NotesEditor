#pragma once
#include "DxLib.h"
#include "Delegate.hpp"
#include "Game.hpp"
#include "GUI.hpp"
#include <vector>

// �{�^����������Ă���Ԃ̃T�C�Y�k����
const int SIZEDIFF = 2;

class Button : public GUI {
private:
	// �{�^���������ꂽ�񐔁i�����ꂽ�ꍇ�Ƀ{�^����؂�ւ���ۂɎg�p�j
	int count;
	//�{�^���̐F
	Color buttonColor;
	// �{�^���̉摜�n���h��
	std::vector<int> handle;
	// �{�^���������ꂽ�ۂɂǂꂾ���傫����ς��邩
	int sub;
	// �{�^���𖄂߂邩
	bool fill;
	// �f���Q�[�g
	DelegateBase<void(void)>* myDg;
	// �{�^���������ꂽ��
	void OnClick() noexcept;
	// �}�E�X�N���b�N�̃`�F�b�N
	bool IsClick() noexcept;
	// �}�E�X���{�^���̏�ɂ��邩�`�F�b�N
	bool IsOnMouse();
	// ���N���b�N���ꂽ��
	bool IsMouseLeftClick();
	// ��N���b�N���̏���
	void NotClick();
	// �N���b�N�񐔃J�E���g
	void ClickCount();
	// �C�x���g�֐����s
	void RunEvent();
	// �摜���ݒ莞�̃{�b�N�X�`��
	void DrawDefaultBox();
	// �摜�ݒ�{�b�N�X�`��
	void DrawImageBox();
	// �{�^���T�C�Y�ύX
	void ChangeButtonSize();

public:
	Button() noexcept;

	~Button() noexcept;

	void Update() noexcept;

	void Draw() noexcept;

	void SetButtonInfo(const int x, const int y, const int w, const int h, const unsigned int color = GetColor(255, 255, 255), const bool f = false) noexcept;//�`��p���̐ݒ�

	// �C�x���g�֐��̐ݒ�
	// �N���b�N���Ɏ��s�����֐����i�[���ꂽDelegate�I�u�W�F�N�g�̐ݒ�
	void SetEventFunction(DelegateBase<void(void)>* dg) noexcept;

	void SetImageHandle(const char* file_name) noexcept;// �摜�̐ݒ�

};