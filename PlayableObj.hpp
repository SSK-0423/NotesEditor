#pragma once
#include "KeyInput.hpp"
//����\�ȃI�u�W�F�N�g�̃C���^�[�t�F�[�X
class PlayableObj {
private:
	//�L�[�{�[�h�A�}�E�X����̊Ǘ�
	virtual void Controll() = 0;
	//�ړ����E
	virtual void PosLimit() = 0;
};