#pragma once
#include "ICollider.hpp"

/*
	�l�p�`�̃q�b�g�{�b�N�X
*/

namespace Game
{
	namespace Object
	{
		namespace Polygon
		{
			class Polygon;
		}
	}

	namespace Component
	{
		class Transform;

		namespace Collider
		{
			class BoxCollider : public ICollider{
			private:
				// �����蔻��g�ƂȂ�|���S��
				Object::Polygon::Polygon* rect;
				// �e��Transform
				const Component::Transform& parentTransform;

				void UpdatePolygon();
			public:
				BoxCollider(const Component::Transform& transform);
				~BoxCollider();
				void Draw();
				void Update();
				Object::Polygon::Polygon GetPolygon() const;
				COLLIDERTYPE GetColliderType() const;
			};
		}
	}
}

/*
	Polygon�̋@�\
	�E�|���S���̐����E�`��

	BoxCollider�̋@�\
	�E�l�p�`�̃q�b�g�{�b�N�X��e�I�u�W�F�N�g�ɂ���@�\(�ӔC)
	�E�q�b�g�{�b�N�X�̕`��
	�E�l�p�`�̃|���S���𐶐�����Ƃ����@�\�͊܂܂�Ă���

	����ŗp����͎̂l�p�`�̃|���S��
	�|���S�����p������Rectangle����闝�R
	�EBoxCollider���l�p�`�̃|���S���ɂȂ�悤�ɁA�_�̒����Ȃǂ��s���Ă���
	�E���Ŏl�p�`�̃|���S������낤�Ƃ����Ƃ��A����Point�I�u�W�F�N�g�𐶐����āA
	AddPoint�ő������K�v������B���ǉ��_�����������菭�Ȃ������肷��\��������B
	�܂��APoint��Polygon��include����K�v�����o�Ă���B��include�������Ȃ�
	�P���ɂ߂�ǂ�����
	�����蔻��ŕK�v�Ȃ̂́AGetVertexList()�̂�
	�����������̓����蔻��ȊO�ł킴�킴�l�p�`�|���S���g���@���H

*/