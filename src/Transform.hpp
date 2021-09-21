#pragma once
#include "Position.hpp"
#include "Rotation.hpp"
#include "Size.hpp"
/*
	���W�E�T�C�Y�E��]�𓝊��Ǘ�����N���X
*/

namespace Game
{

	namespace Component
	{

		class Transform {
		private:
			Position position;
			Rotation rotation;
			Size size;

		public:
			Transform(){}
			Position GetPosition() const
			{
				return position;
			}
			Rotation GetRotation() const
			{
				return rotation;
			}
			Size GetSize() const
			{
				return size;
			}
		};
	}
}

/*
	��������
	���_�FTransform��Positon2D,Size2D,Rotation2D�Ɉˑ����Ă���
	��FPosition3D���ǉ����ꂽ��Transform�ɕύX��������K�v������
	��FPosition2D�ɐ��ʂɓ����@�\���ǉ����ꂽ��Transform���炻����Ăяo���@�\���K�v�ɂȂ�
	����ŁAclass�ɂ���Ƃ��͍��W�̍X�V�E��]�̍X�V�Ȃǂ��ʓ|�ɂȂ�̂ł�
	�Etransform.Position(),transform.Size(),transform.Rotation()
	Position��Position2D�Ƃ��Ă��A���X�R�t�̒u���������������Ȃ�
	��Fz�l���g�p���Ă����
	��3D���킯�ł͂Ȃ��̂�...
*/