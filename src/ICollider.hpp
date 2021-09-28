#pragma once
namespace PolygonObject
{
	class Polygon;
}
namespace Component
{
	namespace Collider
	{
		enum class COLLIDERTYPE
		{
			COLLIDERTYPE_BOX,		// BoxCollider
			COLLIDERTYPE_NUM		// Collider‚ÌŽí—Þ
		};

		class ICollider {
		public:
			virtual ~ICollider() {}
			virtual void Draw() = 0;
			virtual PolygonObject::Polygon GetPolygon() const = 0;
			virtual COLLIDERTYPE GetColliderType() const = 0;
		};
	}
}