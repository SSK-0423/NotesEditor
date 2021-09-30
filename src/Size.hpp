#pragma once
namespace Engine
{
	namespace Components
	{
		class Size {
		private:
			float width;
			float height;

			float scaleWidth;
			float scaleHeight;

		public:
			Size() : width(1.f), height(1.f),scaleWidth(1.f),scaleHeight(1.f) {}
			Size(float w, float h) : width(w), height(h),scaleWidth(1.f),scaleHeight(1.f) {}
			float GetWidth() { return width; } const
			float GetHeight() { return height; } const
			float GetScaleWidth() { return scaleWidth; } const
			float GetScaleHeight() { return scaleHeight; } const
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