#pragma once
namespace Engine
{
	namespace PrimitiveObj
	{
		class Polygon;
		struct Point;
	}
	namespace Collision
	{
		class CrossingNumberAlgorithm {
		private:
		public:
			bool Collision(const PrimitiveObj::Point& point, const PrimitiveObj::Polygon& polygon);
		};
	}
}
