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
			// 画像
			mutable Image imageHandle;
			// 親オブジェクトのTransform
			const Transform& parentTransform;

			float imgWidth;
			float imgHeight;

		public:
			Texture(const Transform& transform, const char* path);

			// テクスチャ描画
			void Draw();

			// テクスチャ読み込み
			void LoadTexture(const char* path) const;

			// テクスチャサイズ取得
			void GetTextureSize(float& w, float& h) const;
		};
	}
}