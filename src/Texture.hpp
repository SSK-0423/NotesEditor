#pragma once

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

		public:
			Texture(const Transform& transform,const char* path) : imageHandle(-1), parentTransform(transform)
			{
				LoadTexture(path);
			}

			// �e�N�X�`���`��
			void Draw();

			// �e�N�X�`���ǂݍ���
			void LoadTexture(const char* path) const;
		};
	}
}