#pragma once
namespace Game
{
	namespace Component
	{
		namespace Collision
		{
			class Point;
			class Polygon;

			class PointAndPolygonImpl {
			public:
				virtual bool Collision(const Point& point, const Polygon& polygon) = 0;
			};
		}
	}
}