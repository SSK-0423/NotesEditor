#pragma once
namespace Game
{
	namespace Object
	{
		namespace Polygon 
		{
			class Polygon;
			struct Point;
		}
	}
	namespace Component
	{
		namespace Collision
		{
			class CrossingNumberAlgorithm {
			private:
			public:
				bool Collision(const Object::Polygon::Point& point, const Object::Polygon::Polygon& polygon);
			};
		}
	}
}