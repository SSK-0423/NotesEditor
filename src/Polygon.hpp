#pragma once
#include <vector>
#include "Point.hpp"

namespace Game
{
	namespace Object
	{
		namespace Polygon
		{
			class Polygon {
			private:
				std::vector<Point> points;
			public:
				Polygon();
				~Polygon();
				void Draw();
				void AddPoint(const Point& point);
			};
		}
	}
}