#pragma once
namespace Component
{
	class Size {
	private:
		float width;
		float height;

	public:
		Size() : width(1.f), height(1.f) {}
		Size(float w, float h) : width(w), height(h) {}
		float GetWidth() { return width; } const
			float GetHeight() { return height; } const

			void Scaling(float x, float y)
		{
			width *= x;
			height *= y;
		}
		void SetSize(float w, float h)
		{
			width = w;
			height = h;
		}
	};
}