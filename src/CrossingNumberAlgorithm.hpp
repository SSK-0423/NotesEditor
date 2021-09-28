#pragma once
namespace PolygonObject
{
	class Polygon;
	struct Point;
}
namespace Component
{
	namespace Collision
	{
		class CrossingNumberAlgorithm {
		private:
		public:
			bool Collision(const PolygonObject::Point& point, const PolygonObject::Polygon& polygon);
		};
	}
}
