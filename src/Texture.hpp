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
			// 画像
			mutable Image imageHandle;
			// 親オブジェクトのTransform
			const Transform& parentTransform;
			// オブジェクトのスクリーン座標
			const Position* parentScreenPos;
			// 位置
			float posX, posY;
			// 角度
			Degree angle;
			// 画像サイズ
			float imgWidth, imgHeight;
			// 描画時のスケール
			double drawScaleWidth, drawScaleHeight;
			
		public:
			Texture(const Transform& transform, const char* path);
			Texture(const Transform& transform, const Position& pos, const char* path);
			Texture(const Transform& transform, const Position& pos, Image handle);
			// テクスチャの位置・サイズ・角度更新
			void Update();
			// テクスチャ描画
			void Draw();
			// テクスチャ読み込み
			void LoadTexture(const char* path) const;
			// テクスチャサイズ取得
			void GetTextureSize(float& w, float& h) const;
			// 画像セット
			void SetImage(Image handle);
		};
	}

}