#pragma once
#include "DxLib.h"
#include "Delegate.hpp"
#include <vector>
#include "Vector2D.hpp"
#include "GameObject.hpp"

class Button : public GameObject {
private:
	int count;							// �{�^���������ꂽ�񐔁i�����ꂽ�ꍇ�Ƀ{�^����؂�ւ���ۂɎg�p�j

	unsigned int buttonColor;			//�{�^���̐F

	std::vector<int> handle;			// �{�^���̉摜�n���h��

	int sub;							//�{�^���������ꂽ�ۂɂǂꂾ���傫����ς��邩

	bool fill;							// �{�^���𖄂߂邩

	bool isPressed;						// �{�^����������Ă��邩�ǂ���

	int OnClick() noexcept;				//�{�^���������ꂽ��

	int IsCheckClick() noexcept;		//�}�E�X�N���b�N�̃`�F�b�N

	DelegateBase<void(void)>* myDg;		// �f���Q�[�g
public:
	Button() noexcept;							//�R���X�g���N�^

	~Button() noexcept;							//�f�X�g���N�^

	void Update() noexcept;						//�X�V

	void Draw() noexcept;						//�{�^���̕`��

	void SetButtonInfo(const int x, const int y, const int w, const int h, const unsigned int color = GetColor(255, 255, 255), const bool f = false) noexcept;//�`��p���̐ݒ�

	// �C�x���g�֐��̐ݒ�
	// �N���b�N���Ɏ��s�����֐����i�[���ꂽDelegate�I�u�W�F�N�g�̐ݒ�
	void SetEventFunction(DelegateBase<void(void)>* dg) noexcept;

	void SetImageHandle(const char* file_name) noexcept;// �摜�̐ݒ�

};