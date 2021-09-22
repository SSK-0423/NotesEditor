#pragma once
namespace Game
{
	namespace Component
	{
		namespace Object
		{
			namespace Polygon 
			{
				class Polygon;
				class Rectangle;
				class Point;
			}
		}
		namespace Collider
		{
			enum class COLLIDERTYPE
			{
				COLLIDERTYPE_BOX,		// BoxCollider
				COLLIDERTYPE_CIRCLE,	// CircleCollider
				COLLIDERTYPE_NUM		// Collider‚ÌŽí—Þ
			};

			class ICollider {
			public:
				virtual void Draw() = 0;
				virtual Object::Polygon::Polygon GetPolygon() const = 0;
				virtual COLLIDERTYPE GetColliderType() const = 0 ;
			};
		}
	}
}