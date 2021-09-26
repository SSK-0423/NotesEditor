#pragma once
#include "GameSymbol.hpp"
namespace Game
{
	using Image = int;
	using Degree = float;
	namespace Component
	{
		class Transform;

		class Texture {
		private:
			// 画像
			mutable Image imageHandle;
			// 親オブジェクトのTransform
			const Transform& parentTransform;

			// 位置
			float posX, posY;
			// 角度
			Degree angle;
			// サイズ
			float sizeWidth, sizeHeight;
			// 画像サイズ
			float imgWidth, imgHeight;

		public:
			Texture(const Transform& transform, const char* path);

			// テクスチャの位置・サイズ・角度更新
			void Update();
			// テクスチャ描画
			void Draw();

			// テクスチャ読み込み
			void LoadTexture(const char* path) const;

			// テクスチャサイズ取得
			void GetTextureSize(float& w, float& h) const;
		};
	}
}