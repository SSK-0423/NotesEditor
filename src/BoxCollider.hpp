#pragma once
#include "ICollider.hpp"

namespace Game
{

	namespace Component
	{

		namespace Collider
		{
			class BoxCollider : public ICollider{
			private:
				Object::Polygon::Rectangle* rect;

			public:
				BoxCollider();
				~BoxCollider();
				void Draw();
				COLLIDERTYPE GetColliderType();
			};
		}
	}
}