#pragma once

namespace Game
{
	using Image = int;

	namespace Component
	{
		class Transform;

		class Texture {
		private:
			// 画像
			mutable Image imageHandle;
			// 親オブジェクトのTransform
			const Transform& parentTransform;

		public:
			Texture(const Transform& transform,const char* path) : imageHandle(-1), parentTransform(transform)
			{
				LoadTexture(path);
			}

			// テクスチャ描画
			void Draw();

			// テクスチャ読み込み
			void LoadTexture(const char* path) const;
		};
	}
}