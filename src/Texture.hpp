#pragma once
#include "GameSymbol.hpp"

namespace Component
{
	class Transform;

	class Texture {
	private:
		// �摜
		mutable Image imageHandle;
		// �e�I�u�W�F�N�g��Transform
		const Transform& parentTransform;

		// �ʒu
		float posX, posY;
		// �p�x
		Degree angle;
		// �T�C�Y
		float sizeWidth, sizeHeight;
		// �摜�T�C�Y
		float imgWidth, imgHeight;

	public:
		Texture(const Transform& transform, const char* path);

		// �e�N�X�`���̈ʒu�E�T�C�Y�E�p�x�X�V
		void Update();
		// �e�N�X�`���`��
		void Draw();

		// �e�N�X�`���ǂݍ���
		void LoadTexture(const char* path) const;

		// �e�N�X�`���T�C�Y�擾
		void GetTextureSize(float& w, float& h) const;
	};
}