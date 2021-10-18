#pragma once
#include "GameUtility.hpp"

/*
* テクスチャクラス
*/

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
			mutable Image imageHandle;
			const Transform& parentTransform;
			float posX, posY;
			Radian angle;
			float imgWidth, imgHeight;
			double drawScaleWidth, drawScaleHeight;

			void UpdatePos();
			void UpdateAngle();
			void UpdateDrawScale();
			double CalcDrawScaleWidth(const Size& size);
			double CalcDrawScaleHeight(const Size& size);
		public:
			Texture(const Transform& transform, const char* path);
			void Update();
			void Draw();
			void LoadTexture(const char* path) const;
			void GetTextureSize(float& w, float& h) const;
		};
	}

}