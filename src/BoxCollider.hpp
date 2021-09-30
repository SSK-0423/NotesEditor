#pragma once
#include "ICollider.hpp"

/*
�l�p�`�̃q�b�g�{�b�N�X
*/

namespace Engine
{
	namespace PrimitiveObj
	{
		class Polygon;
	}
	namespace Components
	{
		class Transform;

		class BoxCollider : public ICollider {
		private:
			// �q�b�g�{�b�N�X
			PrimitiveObj::Polygon* rectHitBox;
			const Transform& parentTransform;
			
			void UpdatePolygon();
		public:
			BoxCollider(const Transform& transform);
			~BoxCollider();
			void Update();
			void Draw();
			PrimitiveObj::Polygon GetPolygon() const;
			COLLIDERTYPE GetColliderType() const;
		};
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