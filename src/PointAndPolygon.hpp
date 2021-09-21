#pragma once
namespace Game
{
	namespace Component
	{
		namespace Collision
		{
			class Point;
			class Polygon;
			class PointAndPolygonImpl;

			class PointAndPolygon {
			private:
				PointAndPolygonImpl* impl;
			public:
				PointAndPolygon(PointAndPolygonImpl* impl): impl(impl){}
				void Collision(const Point& point, const Polygon& polygon);
			};
		}
	}
}