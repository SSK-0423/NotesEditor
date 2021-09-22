#pragma once
namespace Game
{
	namespace Object 
	{

		namespace Polygon 
		{
			class Point;
		}
	}

	namespace Component
	{
		namespace Collider 
		{
			class Collider;
		}

		namespace Collision
		{
			class PointInPolygon {
			public:
				bool Collision(const Object::Polygon::Point& point, const Collider::Collider& collider);
			};
		}
	}
}