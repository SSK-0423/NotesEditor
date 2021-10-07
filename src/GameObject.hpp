#pragma once
#include "GameSymbol.hpp"

namespace Engine
{
	namespace Components
	{
		class Transform;
		class Position;
	}

	class GameObject {
	protected:
		// �I�u�W�F�N�g�̈ʒu�E�T�C�Y
		Components::Transform* transform;
		// �`��p���W
		Components::Position* screenPos;

	public:
		GameObject();
		virtual ~GameObject();

		const Components::Transform& GetTransform() const;
		Components::Transform& GetTransform();

		const Components::Position GetScreenPos() const;
		Components::Position GetScreenPos();

		void UpdateScreenPos(Components::Position pos);
		virtual void Update() = 0;
		virtual void Draw() = 0;
	};
}

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