#pragma once
#include "Vector2D.hpp"
#include "KeyInput.hpp"
//����\�ȃI�u�W�F�N�g�̃C���^�[�t�F�[�X
class PlayableObj {
protected:
	//�I�u�W�F�N�g�̈ړ����E
	Vector2D<float> minLimitPos;	//����(����)
	Vector2D<float> maxLimitPos;	//���(�E��)
private:
	//�L�[�{�[�h�A�}�E�X����̊Ǘ�
	virtual void Controll() = 0;
	//�ړ����E
	virtual void PosLimit() = 0;
public:
	PlayableObj() {
		maxLimitPos.x = 0;
		maxLimitPos.y = 0;
		minLimitPos.x = 0;
		minLimitPos.y = 0;
	}
};