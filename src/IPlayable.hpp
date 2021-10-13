#pragma once
#include "Vector2.hpp"

//����\�ȃI�u�W�F�N�g�̃C���^�[�t�F�[�X
class IPlayable {
protected:
	//�I�u�W�F�N�g�̈ړ����E
	Vector2<float> minLimitPos;	//����(����)
	Vector2<float> maxLimitPos;	//���(�E��)
private:
	//�L�[�{�[�h�A�}�E�X����̊Ǘ�
	virtual void Controll() = 0;
	//�ړ����E
	virtual void LimitPos() = 0;
public:
	// �L�[���͎�t
	// virtual void Input() = 0;
};