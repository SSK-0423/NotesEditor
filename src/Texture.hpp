#pragma once
#include "GameSymbol.hpp"
namespace Game
{
	using Image = int;

	namespace Component
	{
		class Transform;

		class Texture {
		private:
			// �摜
			mutable Image imageHandle;
			// �e�I�u�W�F�N�g��Transform
			const Transform& parentTransform;

			float imgWidth;
			float imgHeight;

		public:
			Texture(const Transform& transform, const char* path);

			// �e�N�X�`���`��
			void Draw();

			// �e�N�X�`���ǂݍ���
			void LoadTexture(const char* path) const;

			// �e�N�X�`���T�C�Y�擾
			void GetTextureSize(float& w, float& h) const;
		};
	}
}