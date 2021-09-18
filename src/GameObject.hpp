#pragma once
#include "Game.hpp"
#include "Transform.hpp"

class GameObject{
protected:

	// �I�u�W�F�N�g�̈ʒu�E�T�C�Y
	Transform transform;

public:
	GameObject() noexcept;
	~GameObject() noexcept;

	const Transform& GetTransform() const
	{
		return transform;
	}

	Transform& GetTransform() 
	{
		return transform;
	}

	virtual void Update() = 0;
	virtual void Draw() = 0;
};

/*
	�Ȃ�Transform���������
	�E�N���X��Transform���������邾���ŁA�ʒu�E�T�C�Y�Ƃ����p�����[�^�Ƃ���getter/setter���������邱�Ƃ��ł��邩��
	�E�������������K�v���Ȃ��Ȃ��Ċy

	Transform��getter���|�C���^�ł͂Ȃ��l��Ԃ��悤�ɂ����
	�ETransform���R���|�W�b�g����N���X�Ɉʒu��T�C�Y��getter/setter�������K�v���o�Ă���
	�ETransform����������R�ɔ�����

	�|�C���^��Ԃ��ۂ̖��_
	�E���W���擾�����������̏ꍇ�ł��A���W�E�T�C�Y�̕ύX���\�ɂȂ��Ă��܂�
	�@��FCamera2D::Collision
*/