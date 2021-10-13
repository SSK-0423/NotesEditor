#pragma once

namespace Engine
{
	namespace PrimitiveObj
	{
		class Polygon;
	}
	namespace Components
	{
		enum class COLLIDERTYPE
		{
			COLLIDERTYPE_BOX,		// BoxCollider
			COLLIDERTYPE_NUM		// Collider‚ÌŽí—Þ
		};

		class ICollider {
		public:
			virtual ~ICollider() {}
			virtual void Update() = 0;
			virtual void Draw() = 0;
			virtual PrimitiveObj::Polygon GetPolygon() const = 0;
			virtual COLLIDERTYPE GetColliderType() const = 0;
		};
	}
}