#pragma once
#include "ICollider.hpp"

/*
	�l�p�`�̓����蔻��̂��߂̃I�u�W�F�N�g
*/

namespace Game
{
	namespace Object
	{
		namespace Polygon
		{
			class Polygon;
		}
	}

	namespace Component
	{
		class Transform;

		namespace Collider
		{
			class BoxCollider : public ICollider{
			private:
				// �����蔻��ƂȂ�|���S��
				//Object::Polygon::Rectangle* rect;
				Object::Polygon::Polygon* rect;
				// �e��Transform
				const Component::Transform& parentTransform;
				void UpdatePolygon();
			public:
				BoxCollider(const Component::Transform& transform);
				~BoxCollider();
				void Draw();
				void Update();
				Object::Polygon::Polygon GetPolygon() const;
				COLLIDERTYPE GetColliderType() const;
			};
		}
	}
}