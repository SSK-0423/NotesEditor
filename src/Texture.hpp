#pragma once
#include "GameSymbol.hpp"

namespace Engine
{
	class GameObject;

	namespace Components
	{
		class Transform;
		class Position;
		class Rotation;
		class Size;

		class Texture {
		private:
			// �摜
			mutable Image imageHandle;
			// �e�I�u�W�F�N�g��Transform
			const Transform& parentTransform;
			// �I�u�W�F�N�g�̃X�N���[�����W
			const Position* parentScreenPos;
			// �ʒu
			float posX, posY;
			// �p�x
			Degree angle;
			// �摜�T�C�Y
			float imgWidth, imgHeight;
			// �`�掞�̃X�P�[��
			double drawScaleWidth, drawScaleHeight;
			
		public:
			Texture(const Transform& transform, const char* path);
			Texture(const Transform& transform, const Position& pos, const char* path);
			Texture(const Transform& transform, const Position& pos, Image handle);
			// �e�N�X�`���̈ʒu�E�T�C�Y�E�p�x�X�V
			void Update();
			// �e�N�X�`���`��
			void Draw();
			// �e�N�X�`���ǂݍ���
			void LoadTexture(const char* path) const;
			// �e�N�X�`���T�C�Y�擾
			void GetTextureSize(float& w, float& h) const;
			// �摜�Z�b�g
			void SetImage(Image handle);
		};
	}

}