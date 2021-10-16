#pragma once

/*
* オブジェクトのサイズクラス
*/

namespace Engine
{
	namespace Components
	{
		class Size {
		public:
			// スケール１の時のサイズを保持しておきたいので、
			// サイズとスケールの変数を分けている
			float width;
			float height;
			float scaleWidth;
			float scaleHeight;

			Size() : width(1.f), height(1.f), scaleWidth(1.f), scaleHeight(1.f) {}
			Size(float w, float h) : width(w), height(h), scaleWidth(1.f), scaleHeight(1.f) {}
			void SetSize(float w, float h)
			{
				width = w;
				height = h;
			}
			void Scaling(float scaleW, float scaleH)
			{
				scaleWidth = scaleW;
				scaleHeight = scaleH;
			}
		};
	}
}