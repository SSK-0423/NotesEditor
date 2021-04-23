#pragma once
#include "DxLib.h"
#include "Music.hpp"
#include "Delegate.hpp"
#include <vector>
//�`��̍���E�����W(x,y)
struct Vector2
{
	int x;
	int y;
};

class Button {
private:
	Vector2 position; // �{�^���̍��W

	int height; // �{�^���̍���

	int width; // �{�^���̕�

	int count;// �{�^���������ꂽ�񐔁i�����ꂽ�ꍇ�Ƀ{�^����؂�ւ���ۂɎg�p�j

	unsigned int buttonColor;//�{�^���̐F

	std::vector<int> handle; // �{�^���̉摜�n���h��

	int sub; //�{�^���������ꂽ�ۂɂǂꂾ���傫����ς��邩

	bool fill;// �{�^���𖄂߂邩

	bool isPressed; // �{�^����������Ă��邩�ǂ���

	int OnClick();//�{�^���������ꂽ��

	void CheckClick();//�}�E�X�N���b�N�̃`�F�b�N

	DelegateBase<void(void)>* myDg; // �f���Q�[�g
public:
	Button();//�R���X�g���N�^

	~Button();//�f�X�g���N�^

	void Update();//�X�V

	void Draw();//�{�^���̕`��
	
	void SetButtonInfo(const int x, const int y , const int w, const int h, const unsigned int color = GetColor(255,255,255), const bool f = false);//�`��p���̐ݒ�
	//�{�^���̍��W�w��
	//void SetPosition(const int x, const int y);
	//void SetButotnInfo_Image(const int& x1, const int& y1, const int& x2, const int& y2, const unsigned int& color, const bool& f);
	// �C�x���g�֐��̐ݒ�
	// �N���b�N���Ɏ��s�����֐����i�[���ꂽDelegate�I�u�W�F�N�g�̐ݒ�
	void SetEventFunction(DelegateBase<void(void)>* dg);
	
	void SetImageHandle(const char* file_name);// �摜�̐ݒ�

};