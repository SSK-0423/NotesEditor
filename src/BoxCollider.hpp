#pragma once
namespace Game
{
	namespace Object
	{
		namespace Polygon
		{
			class Rectangle;
		}
	}
	namespace Component
	{
		namespace Collider
		{
			class BoxCollider {
			private:
				Object::Polygon::Rectangle* rect;
			public:
				BoxCollider();
				~BoxCollider();
			};
		}
	}
}